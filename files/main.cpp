////main.cpp
//#include "provided.h"
//#include "PersonProfile.h"
//#include "AttributeTranslator.h"
//#include "MemberDatabase.h"
//#include "MatchMaker.h"
//
//#include <iostream>
//#include <string>
//#include <vector>
//using namespace std;
//
//const std::string MEMBERS_FILE = "members.txt";
//const std::string TRANSLATOR_FILE = "translator.txt";
//const std::string TESTMEM = "testmember.txt";
//
//int main()
//{
//	//PersonProfile pf("John", "John@gmail.com");
//	//cout << pf.GetName() << endl;
//	//cout << pf.GetEmail() << endl;
//	//AttValPair av1("hobby", "swimming");
//	//pf.AddAttValPair(av1);
//	//cout << pf.GetNumAttValPairs() << endl;
//	//AttValPair avn;
//	//pf.GetAttVal(0, avn);
//	//AttValPair debug; 
//
//	//testcases for personprofile
//
//	/*AttributeTranslator atr;
//	if (!atr.Load(TRANSLATOR_FILE)) {
//		std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//		return 1;
//	}
//	vector<AttValPair> atvp = atr.FindCompatibleAttValPairs(AttValPair("job", "chef"));
//	for (int i = 0; i < atvp.size(); i++) {
//		cout << atvp[i].attribute << endl;
//		cout << atvp[i].value << endl;
//		cout << endl;
//	}*/
//
//	//testcases for attributetranslator
//
//	//MemberDatabase mdb;
//	//if (!mdb.LoadDatabase(TESTMEM))
//	//{
//	//	std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//	//	return 1;
//	//}
//	//if (mdb.GetMemberByEmail("nothing") == nullptr) {
//	//	//cout << "nothing here" << endl;
//	//}
//	//for (int i = 0; i < mdb.GetMemberByEmail("AbFow2483@charter.net")->GetNumAttValPairs(); i++) {
//	//	AttValPair atr;
//	//	mdb.GetMemberByEmail("AbFow2483@charter.net")->GetAttVal(i, atr);
//	//	//cout << atr.attribute << " " << atr.value << endl;
//	//}
//	//vector<string> emails;
//	//emails = mdb.FindMatchingMembers(AttValPair("job", "editor"));
//	//if (emails.empty())
//	//	cout << "Nothing same" << endl;
//	//for (int i = 0; i < emails.size(); i++) {
//	//	cout << emails[i] << endl;
//	//}
//
//	//testcases for memberdatabase
//
//	//MemberDatabase mdb;
//	//if (!mdb.LoadDatabase(MEMBERS_FILE))
//	//{
//	//	std::cout << "Error loading " << TESTMEM << std::endl;
//	//	return 1;
//	//}
//	//AttributeTranslator atr;
//	//if (!atr.Load(TRANSLATOR_FILE)) {
//	//	std::cout << "Error loading " << MEMBERS_FILE << std::endl;
//	//	return 1;
//	//}
//	//MatchMaker mm(mdb, atr);
//	////check with bad email
//	//vector<EmailCount> bestmatches_emails = mm.IdentifyRankedMatches("AugustusBarr87744@charter.net", 5);
//	//for (int i = 0; i < bestmatches_emails.size(); i++) {
//	//	cout << bestmatches_emails[i].email << " " << bestmatches_emails[i].count << endl;
//	//}
//
//	//testcases for matchmaker
//
//}

//main.cpp

#include "PersonProfile.h"
#include "AttributeTranslator.h"
#include "MemberDatabase.h"
#include "MatchMaker.h"
#include "provided.h"
#include <iostream>
#include <string>
#include <vector>

const std::string MEMBERS_FILE = "members.txt";
const std::string TRANSLATOR_FILE = "translator.txt";

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at);

int main() {
    MemberDatabase mdb;
    if (!mdb.LoadDatabase(MEMBERS_FILE))
    {
        std::cout << "Error loading " << MEMBERS_FILE << std::endl;
        return 1;
    }
    AttributeTranslator at;
    if (!at.Load(TRANSLATOR_FILE))
    {
        std::cout << "Error loading " << TRANSLATOR_FILE << std::endl;
        return 1;
    }

    while (findMatches(mdb, at))
        ;

    std::cout << "Happy dating!" << std::endl;
}

bool findMatches(const MemberDatabase& mdb, const AttributeTranslator& at)
{
    // Prompt for email
    std::string email;
    const PersonProfile* pp;
    for (;;) {
        std::cout << "Enter the member's email for whom you want to find matches: ";
        std::getline(std::cin, email);
        if (email.empty())
            return false;
        pp = mdb.GetMemberByEmail(email);
        if (pp != nullptr)
            break;
        std::cout << "That email is not in the member database." << std::endl;
    }

    // Show member's attribute-value pairs
    std::cout << "The member has the following attributes:" << std::endl;
    for (int k = 0; k != pp->GetNumAttValPairs(); k++) {
        AttValPair av;
        pp->GetAttVal(k, av);
        std::cout << av.attribute << " --> " << av.value << std::endl;
    }

    // Prompt user for threshold
    int threshold;
    std::cout << "How many shared attributes must matches have? ";
    std::cin >> threshold;
    std::cin.ignore(10000, '\n');

    // Print matches and the number of matching translated attributes
    MatchMaker mm(mdb, at);
    std::vector<EmailCount> emails = mm.IdentifyRankedMatches(email, threshold);
    if (emails.empty())
        std::cout << "No member was a good enough match." << std::endl;
    else {
        std::cout << "The following members were good matches:" << std::endl;;
        for (const auto& emailCount : emails) {
            const PersonProfile* pp = mdb.GetMemberByEmail(emailCount.email);
            std::cout << pp->GetName() << " at " << emailCount.email << " with "
                << emailCount.count << " matches!" << std::endl;
        }
    }
    std::cout << std::endl;
    return true;
}