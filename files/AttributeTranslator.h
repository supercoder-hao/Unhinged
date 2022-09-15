#ifndef ATTRIBUTETRANSLATOR_H_
#define ATTRIBUTETRANSLATOR_H_

#include "provided.h"
#include "RadixTree.h"

#include <string>
#include <vector>
using namespace std;

class AttributeTranslator
{
public:
	AttributeTranslator();
	~AttributeTranslator();
	bool Load(std::string filename);
	std::vector<AttValPair> FindCompatibleAttValPairs(const AttValPair& source) const;

private:
	RadixTree<vector<AttValPair>> m_translation;
};

#endif