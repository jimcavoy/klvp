#include <klvp/klvuselmtimpl.h>

lcss::UniversalMetadataElement::UniversalMetadataElement(uint8_t* key)
{
	for (int i = 0; i < 16; i++)
		key_.push_back(key[i]);
}

lcss::UniversalMetadataElement::~UniversalMetadataElement()
{

}