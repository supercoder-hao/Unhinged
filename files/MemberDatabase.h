#ifndef MEMBERDATABASE_H_
#define MEMBERDATABASE_H_

#include "provided.h"
#include "RadixTree.h"
#include "PersonProfile.h"

#include <vector>
using namespace std;

class MemberDatabase
{
public:
	MemberDatabase();
	~MemberDatabase();
	bool LoadDatabase(std::string filename);
	std::vector<std::string> FindMatchingMembers(const AttValPair& input) const;
	const PersonProfile* GetMemberByEmail(std::string email) const;

private:
	RadixTree<PersonProfile*> m_profiles;
	RadixTree<vector<string>> m_pairstoem;
};

#endif