#include "FpParser.h"

#include <cmath>
#include <cstdint>
#include <memory.h>
#ifdef WIN32
#include <winsock2.h>
#else
#include <netinet/in.h>
#endif

uint64_t ntohll ( uint64_t Value );
uint64_t htonll ( uint64_t Value );

static uint8_t POSITIVE_INFINITY_HIGH_BYTE = 0xC8;
static uint8_t NEGATIVE_INFINITY_HIGH_BYTE = 0xE8;
static uint8_t POSITIVE_QUIET_NAN_HIGH_BYTE = 0xD0;
static uint8_t NEGATIVE_QUIET_NAN_HIGH_BYTE = 0xF0;
static uint8_t HIGH_BYTE_MASK = 0xF8;

FpParser::FpParser()
{
	computeConstants(0, 100.0, 4);
}

FpParser::FpParser(double min, double max, int length)
{
	computeConstants(min, max, length);
}

void FpParser::computeConstants(double min, double max, int length)
{
	_a = min;
	_b = max;
	_length = length;
	_zOffset = 0.0;
	_bPow = ceil(log2(_b - _a));
	_dPow = (double)(8 * (uint64_t)_length - 1);
	_sF = exp2(_dPow - _bPow);
	_sR = exp2(_bPow - _dPow);

	if (_a < 0 && _b > 0) {
		_zOffset = _sF * _a - floor(_sF * _a);
	}
}


int FpParser::encode(unsigned char* buffer, int bufsiz, double value)
{
	int ret = 0;
	if (bufsiz != _length) {
		return 1;
	}

	if (std::isinf(value)) {
		memset(buffer, 0, bufsiz);
		buffer[0] = POSITIVE_INFINITY_HIGH_BYTE;
	}
	else if (std::isnan(value)) {
		memset(buffer, 0, bufsiz);
		buffer[0] = POSITIVE_QUIET_NAN_HIGH_BYTE;
	}
	else if (value < _a || value > _b) {
		return 2;
	}
	else { // The passed in value is normal and in range
		double d = trunc(_sF * (value - _a) + _zOffset);
		switch (_length)
		{
		case 1:
			buffer[0] = (uint8_t)d;
			break;
		case 2:
		{
			short s = (short)d;
			s = htons(s);
			memcpy(buffer, &s, 2);
		} break;
		case 3:
		{
			int i = (int)d;
			uint8_t temp[4]{};
			memcpy(temp, &i, 4);
			// place in network order (i.e. Big Endian)
			buffer[0] = temp[2];
			buffer[1] = temp[1];
			buffer[2] = temp[0];
		} break;
		case 4:
		{
			int i = (int)d;
			i = htonl(i);
			memcpy(buffer, &i, 4);
		} break;
		case 5:
		case 6:
		case 7:
		{
			long long ll = (long long)d;
			ll = htonll(ll);
			uint8_t temp[8];
			memcpy(temp, &ll, 8);
			for (int lv = 0; lv < _length; ++lv) {
				int bufferIndex = lv + 8 - _length;
				buffer[lv] = temp[bufferIndex];
			}
		} break;
		case 8:
		{
			long long ll = (long long)d;
			ll = htonll(ll);
			memcpy(buffer, &ll, 8);
		} break;
		}
	}
	return ret;
}

double FpParser::decode(const unsigned char* buffer, int bufsiz)
{
	if (bufsiz > _length)
		return nan("");

	if ((buffer[0] & 0x80) == 0x00)
	{
		return decodeAsNormalMappedValue(buffer, bufsiz);
	}
	// Check if it is -1
	else if (buffer[0] == 0x80) {
		bool allZeros = true;
		for (int i = 1; i < bufsiz; i++) {
			if (buffer[i] != 0x00) {
				allZeros = false;
				break;
			}
		}
		if (allZeros) {
			return decodeAsNormalMappedValue(buffer, bufsiz);
		}
	}

	uint8_t highByteBits = buffer[0] & HIGH_BYTE_MASK;
	if (highByteBits == POSITIVE_INFINITY_HIGH_BYTE) {
		return INFINITY;
	}
	else if (highByteBits == NEGATIVE_INFINITY_HIGH_BYTE) {
		return INFINITY;
	}
	else {
		return nan("");
	}
}

double FpParser::decodeAsNormalMappedValue(const unsigned char* valueBuffer, int bufsiz)
{
	double val = 0.0;

	switch (_length)
	{
	case 1:
	{
		int b1 = (int)valueBuffer[0];
		val = _sR * (b1 - _zOffset) + _a;
	} break;
	case 2:
	{
		short nVal;
		memcpy(&nVal, valueBuffer, 2);
		nVal = ntohs(nVal);
		val = _sR * (nVal - _zOffset) + _a;
	} break;
	case 3:
	{
		int nVal = 0;
		memcpy(&nVal, valueBuffer, 3);
		nVal = ntohl(nVal);
		nVal = nVal >> 8;
		val = _sR * (nVal - _zOffset) + _a;
	} break;
	case 4:
	{
		int nVal = 0;
		memcpy(&nVal, valueBuffer, 4);
		nVal = ntohl(nVal);
		val = _sR * (nVal - _zOffset) + _a;
	} break;
	case 5:
	case 6:
	case 7:
	case 8:
	{
		long long nVal = 0;
		memcpy(&nVal, valueBuffer, 8);
		nVal = ntohll(nVal);
		int shift = (8 - _length) * 8;
		nVal = nVal >> shift;
		val = _sR * (nVal - _zOffset) + _a;
	}
	break;
	}
	return val;
}
