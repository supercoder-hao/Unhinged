#include "PersonProfile.h"
#include "provided.h"

#include <string>
#include <vector>
using namespace std;

PersonProfile::PersonProfile(std::string name, std::string email)
	:m_name(name), m_email(email)
{}

PersonProfile::~PersonProfile()
{}

std::string PersonProfile::GetName() const { return m_name; }

std::string PersonProfile::GetEmail() const { return m_email; }

void PersonProfile::AddAttValPair(const AttValPair& attval)
{
	int setsize = m_valueset.size();
	m_valueset.insert(attval.value);

	if (m_valueset.size() > setsize) {
		m_attributes.push_back(attval.attribute);
		m_values.push_back(attval.value);
	}

	m_attrTree.insert(attval.attribute, m_valueset);
}

int PersonProfile::GetNumAttValPairs() const
{
	return m_valueset.size();
}

bool PersonProfile::GetAttVal(int attribute_num, AttValPair& attval) const
{
	if (attribute_num < 0 || attribute_num > m_valueset.size())
		return false;

	attval = AttValPair(m_attributes[attribute_num], m_values[attribute_num]);
	return true;
}