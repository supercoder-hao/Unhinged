#ifndef MATCHMAKER_H_
#define MATCHMAKER_H_

#include "provided.h"
#include "RadixTree.h"

#include "MemberDatabase.h"
#include "AttributeTranslator.h"

#include <algorithm>
using namespace std;

class MatchMaker
{
public:
	MatchMaker(const MemberDatabase& mdb, const AttributeTranslator& at);
	~MatchMaker();
	std::vector<EmailCount> IdentifyRankedMatches(std::string email, int threshold) const;

private:
	MemberDatabase m_mdb;
	AttributeTranslator m_at;

	static bool compareFinal(const EmailCount& ec1, const EmailCount& ec2) {
		if (ec1.count == ec2.count) {
			return lexicographical_compare(ec1.email.begin(), ec1.email.end(), ec2.email.begin(), ec2.email.end());
		}
		else {
			return (ec1.count >= ec2.count);
		}
	}
};

#endif