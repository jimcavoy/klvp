#include <klvp/util.h>
#include <klvp/KlvSizeVisitor.h>
#include <klvp/treenode.h>

#ifdef _WIN32
#include <WinSock2.h>
#else
#include <netinet/in.h>
#endif

#include <klvp/RawSerializedVisitor.h>

#include <cstdint>


#define TreeNodePtr TreeNode<lcss::KLVElement>*

namespace
{
	void setChecksum(std::vector<uint8_t>& rawByteSeq, uint16_t bcc)
	{
		uint8_t val[2];
		bcc = htons(bcc);
		memcpy(val, &bcc, 2);

		rawByteSeq[rawByteSeq.size() - 2] = val[0];
		rawByteSeq[rawByteSeq.size() - 1] = val[1];
	}
}

const uint8_t lcss::LocalSetKey[] = { 0x06,0x0E,0x2B,0x34,
	0x02,0x0B,0x01,0x01,
	0x0E,0x01,0x03,0x01,
	0x01,0x00,0x00,0x00 };

const uint8_t lcss::SecurityMetadataUniversalSetKey[] = { 0x06,0x0E,0x2B,0x34,
0x02,0x01,0x01,0x01,
0x02,0x08,0x02,0x00,
0x00,0x00,0x00,0x00 };

const uint8_t lcss::UniversalMetadataSetKey[] = { 0x06,0x0E,0x2B,0x34,
0x02,0x01,0x01,0x01,
0x0E,0x01,0x01,0x02,
0x01,0x01,0x00,0x00 };

bool lcss::isLDSGroup(unsigned char key[], int len)
{
	if (key == nullptr || len == 0)
		return false;

	for (int i = 0; i < len; i++)
	{
		if (i > 15)
			return false;
		if (key[i] != lcss::LocalSetKey[i++])
			return false;
	}
	return true;
}

std::vector<unsigned char> lcss::serializeKlvSet(TreeNodePtr root)
{
	std::vector<uint8_t> rawByteSeq;

	KlvSizeVisitor sizeVis;
	auto sizeLamda = [&sizeVis](TreeNodePtr node) { node->getData().Accept(sizeVis); };
	postorderTreeWalk(root, sizeLamda);

	// Serialize the tree instance out to a vector
	RawSerializeVisitor rawSerialVis(rawByteSeq);
	auto serializeLamda = [&rawSerialVis](TreeNodePtr node) { node->getData().Accept(rawSerialVis); };
	preorderTreeWalk(root, serializeLamda);

	// Calculated the checksum
	uint16_t bcc = lcss::bcc_16(rawByteSeq.begin(), rawByteSeq.end() - 2);

	// Set checksum
	setChecksum(rawByteSeq, bcc);

	return rawByteSeq;
}
