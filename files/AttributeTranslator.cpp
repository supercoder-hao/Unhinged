#include "AttributeTranslator.h"
#include "provided.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

AttributeTranslator::AttributeTranslator()
{}

AttributeTranslator::~AttributeTranslator()
{}

bool AttributeTranslator::Load(std::string filename)
{
	std::ifstream infile(filename);

	if (!infile)
		return false;

	if (infile.is_open()) {
		std::string line;

		while (std::getline(infile, line)) {
			std::stringstream oss(line);

			std::string source_attribute, source_value, compatible_attribute, compatible_value;
			std::getline(oss, source_attribute, ',');
			std::getline(oss, source_value, ',');
			std::getline(oss, compatible_attribute, ',');
			std::getline(oss, compatible_value, ',');

			vector<AttValPair> newAttValpair;

			string source = source_attribute + "," + source_value;
			if (m_translation.search(source) == nullptr) {
				//insert a new source with it's compatiable
				newAttValpair.push_back(AttValPair(compatible_attribute, compatible_value));
				m_translation.insert(source, newAttValpair);
			}
			else {
				//insert to existing source's compatiable
				if (find(m_translation.search(source)->begin(), m_translation.search(source)->end(), AttValPair(compatible_attribute, compatible_value)) == m_translation.search(source)->end())
					(m_translation.search(source)->push_back(AttValPair(compatible_attribute, compatible_value)));
			}

		}
	}
	return true;
}

std::vector<AttValPair> AttributeTranslator::FindCompatibleAttValPairs(const AttValPair& source) const
{
	string string_source = source.attribute + "," + source.value;
	vector<AttValPair>* compatible = m_translation.search(string_source);

	if (compatible == nullptr) {
		return vector<AttValPair>();
	}
	else
		return *compatible;
}