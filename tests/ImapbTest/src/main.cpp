/// Floating Point Parser Test
/// Encode and decode floating point values as per MISB ST 1201
/// using the IMAPB algorithm.

#include <klvp/FpParser.h>
#include <iostream>
#include <iomanip>

#define LEN 3

int main()
{
	using namespace std;

	unsigned char buffer[LEN];
	memset(buffer, 0, LEN);
	double dValue = 13898.5463;

	// MISB ST 0601 Tag 96 Target Width Extended example
	FpParser fp(0.0, 1500000.0, LEN);

	int ret = fp.encode(buffer, LEN, dValue);
	// Non-zero is an error
	if (ret > 0) {
		return ret;
	}
	else {
		cout << "Encoding " << setprecision(10) << dValue;
		cout << " => " << showbase << hex;
		for (int i = 0; i < LEN; i++) {
			cout << (int)buffer[i] << " ";
		}
		cout << dec << endl;

		double decodedValue = fp.decode(buffer, LEN);
		cout << "Decoding " << showbase << hex;
		for (int i = 0; i < LEN; i++) {
			cout << (int)buffer[i] << " ";
		}
		cout << "=> " << dec << decodedValue << endl;
	}

	// Special cases
	memset(buffer, 0, LEN);
	dValue = nan("");
	fp.encode(buffer, LEN, dValue);
	double decodedValue = fp.decode(buffer, LEN);

	if (isnan(decodedValue)) {
		cout << "Decoded NaN successfully" << endl;
	}
	else {
		return 3;
	}


	fp.encode(buffer, LEN, INFINITY);
	decodedValue = fp.decode(buffer, LEN);

	if (isinf(decodedValue)) {
		cout << "Decoded Infinity successfully" << endl;
	}
	else {
		return 4;
	}

	return 0;
}