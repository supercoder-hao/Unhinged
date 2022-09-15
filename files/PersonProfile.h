#ifndef PERSONPROFILE_H_
#define PERSONPROFILE_H_

#include "provided.h"
#include "RadixTree.h"

#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

class PersonProfile
{
public:
	PersonProfile(std::string name, std::string email);
	~PersonProfile();
	std::string GetName() const;
	std::string GetEmail() const;
	void AddAttValPair(const AttValPair& attval);
	int GetNumAttValPairs() const;
	bool GetAttVal(int attribute_num, AttValPair& attval) const;

private:
	string m_name;
	string m_email;

	vector<string> m_attributes;
	vector<string> m_values;

	unordered_set<string> m_valueset;
	RadixTree<unordered_set<string>> m_attrTree;
};

#endif