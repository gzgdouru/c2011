#include <iostream>
#include <string>
#include <regex>
using namespace std;

void test_regex_match()
{
	if (std::regex_match("subject", std::regex("(sub)(.*)")))
	{
		cout << "1.string literal matched\n";
	}

	string szStr = "subject";
	regex re = regex("(sub)(.*)");
	if (regex_match(szStr, re))
	{
		cout << "2.string object matched\n";
	}

	if (regex_match(szStr.begin(), szStr.end(), re))
	{
		cout << "3.range matched\n";
	}
	
	cmatch cm;
	regex_match("subject", cm, re);
	cout << "string literal with " << cm.size() << " matches\n";

	smatch sm;
	regex_match(szStr, sm, re);
	cout << "string object with " << sm.size() << " matches\n";

	regex_match(szStr.cbegin(), szStr.cend(), sm, re);
	cout << "range with " << sm.size() << " matches\n";

	regex_match("subject", cm, re, regex_constants::match_default);
	std::cout << "the matches were: ";
	for (int i = 0; i < cm.size(); ++i)
	{
		std::cout << "[" << sm[i] << "] ";
	}
	cout << endl;
}

void test_regex_search()
{
	string szStr = "this subject has a submarine as a subsequence";
	smatch sm;
	regex re("\\b(sub)([^ ]*)");

	if (regex_match(szStr, sm, re))
	{
		cout << "string object with " << sm.size() << " matches\n";
	}
	else
	{
		cout << "not match..." << endl;
	}

	std::cout << "Target sequence: " << szStr << std::endl;
	std::cout << "Regular expression: /\\b(sub)([^ ]*)/" << std::endl;
	std::cout << "The following matches and submatches were found:" << std::endl;

	while (regex_search(szStr, sm, re))
	{
		copy(sm.begin(), sm.end(), ostream_iterator<string>(cout, " "));
		cout << endl;
		std::cout << "--> ([^ ]*) match " << sm.format("$2") << std::endl;
		
		szStr = sm.suffix().str();
		cout << szStr << endl;
	}
}

void test_regex_replace()
{
	string szStr = "there is a subsequence in the string";
	regex re("\\b(sub)([^ ]*)");
	cout << regex_replace(szStr, re, "sub-$2") << endl;
	cout << szStr << endl;

	string szResult;
	regex_replace(back_inserter(szResult), szStr.begin(), szStr.end(), re, "$2");
	cout << szResult << endl;

	cout << regex_replace(szStr, re, "$1 and $2", regex_constants::format_no_copy) << endl;
	cout << szStr << endl;
}

int main(int argc, char *argv[])
{
	//test_regex_match();
	test_regex_search();
	//test_regex_replace();

	getchar();
	return 0;
}