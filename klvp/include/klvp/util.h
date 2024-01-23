#pragma once

#include <vector>
#include "treenode.h"
#include "klvelmt.h"

namespace lcss
{
	extern const unsigned char LocalSetKey[16];
	extern const unsigned char UniversalMetadataSetKey[16];
	extern const unsigned char SecurityMetadataUniversalSetKey[16];

	// Template function to calculate checksum
	// Ref: MISB ST 0601.14a, 1 May 2020, page 31
	template<typename T>
	unsigned short bcc_16(T first, T last)
	{
		// Initialize Checksum and counter variables.
		unsigned short bcc = 0;
		unsigned short i = 0;
		T it;
		// Sum each 16-bit chunk within the buffer into a checksum
		for (it = first; it != last; ++it, i++)
			bcc += *it << (8 * ((i + 1) % 2));
		return bcc;
	} // end of bcc_16 ()

	bool isLDSGroup(unsigned char key[], int len);

	std::vector<unsigned char> serializeKlvSet(TreeNode<lcss::KLVElement>* root);
}