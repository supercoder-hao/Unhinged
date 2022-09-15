#include "MatchMaker.h"
#include "PersonProfile.h"

#include <set>
#include <algorithm>
using namespace std;

MatchMaker::MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at)
	:m_mdb(mdb), m_at(at)
{}

MatchMaker::~MatchMaker()
{}

std::vector<EmailCount> MatchMaker::IdentifyRankedMatches(std::string email, int threshold) const
{
	if (threshold <= 0)
		threshold = 1;

	vector<string> emails;
	RadixTree<int> m_email_comp;
	set<string> nondup_emails;

	vector<EmailCount> matchingEmails;

	if (m_mdb.GetMemberByEmail(email) == nullptr)
		return matchingEmails;

	PersonProfile pf = *m_mdb.GetMemberByEmail(email);
	for (int i = 0; i < pf.GetNumAttValPairs(); i++) {
		AttValPair atp;
		pf.GetAttVal(i, atp);

		vector<AttValPair> vatp = m_at.FindCompatibleAttValPairs(atp);

		vector<string> temp_emails;
		for (int j = 0; j < vatp.size(); j++) {
			if (!m_mdb.FindMatchingMembers(vatp[j]).empty()) {
				temp_emails = (m_mdb.FindMatchingMembers(vatp[j]));
				for (int k = 0; k < temp_emails.size(); k++) {
					emails.push_back(temp_emails[k]);
				}
			}
			//emails.insert(emails.end(), m_mdb.FindMatchingMembers(vatp[i]).begin(), m_mdb.FindMatchingMembers(vatp[i]).end());
		}
	}

	for (int i = 0; i < emails.size(); i++) {
		nondup_emails.insert(emails[i]);

		if (m_email_comp.search(emails[i]) == nullptr) {
			m_email_comp.insert(emails[i], 1);
		}
		else {
			m_email_comp.insert(emails[i], *(m_email_comp.search(emails[i])) + 1);
		}
	}

	set<string>::iterator it = nondup_emails.begin();
	while (it != nondup_emails.end()) {
		if (*m_email_comp.search((*it)) >= threshold) {
			if ((*it) != email) {
				matchingEmails.push_back(EmailCount((*it), *m_email_comp.search((*it))));
			}
		}
		it++;
	}

	sort(matchingEmails.begin(), matchingEmails.end(), &compareFinal);

	return matchingEmails;
}