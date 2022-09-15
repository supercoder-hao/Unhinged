#include "MemberDatabase.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

MemberDatabase::MemberDatabase()
{}

MemberDatabase::~MemberDatabase()
{}

bool MemberDatabase::LoadDatabase(std::string filename)
{
	ifstream infile(filename);

	if (!infile)
		return false;

	if (infile.is_open()) {
		string line;

		string name, email;

		int index = 0;
		int intattamount;
		PersonProfile* newPointerProfile = nullptr;
		while (getline(infile, line)) {
			if (line.empty()) {
				m_profiles.insert(email, newPointerProfile);
				//delete newPointerProfile;
				index = 0;
			}
			else {
				if (index == 0) {
					name = line;
					index++;
				}
				else if (index == 1) {
					email = line;
					newPointerProfile = new PersonProfile(name, email);
					index++;
				}
				else if (index == 2) {
					//attamount = line;
					//intattamount = stoi(attamount);
					index++;
				}

				else {
					string attpair, att, pair;
					attpair = line;
					stringstream oss(attpair);

					getline(oss, att, ',');
					getline(oss, pair, ',');

					if (m_pairstoem.search(attpair) == nullptr) {
						vector<string> emails;
						m_pairstoem.insert(attpair, emails);
						m_pairstoem.search(attpair)->push_back(email);
					}
					else {
						m_pairstoem.search(attpair)->push_back(email);
					}

					newPointerProfile->AddAttValPair(AttValPair(att, pair));
				}
			}
		}
		if (line.empty()) {
			m_profiles.insert(email, newPointerProfile);
			//delete newPointerProfile;
			index = 0;
		}
		delete newPointerProfile;
	}
}

std::vector<std::string> MemberDatabase::FindMatchingMembers(const AttValPair& input) const
{
	vector<string> emails;
	string inputstring = input.attribute + "," + input.value;

	if (m_pairstoem.search(inputstring) == nullptr)
		return emails;

	return *m_pairstoem.search(inputstring);
}

const PersonProfile* MemberDatabase::GetMemberByEmail(std::string email) const
{
	if (m_profiles.search(email) != nullptr)
		return *m_profiles.search(email);
	return nullptr;

}