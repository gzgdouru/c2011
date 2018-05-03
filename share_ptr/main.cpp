#include <iostream>
#include <memory>
#include <string>
using namespace std;

class CExample
{
public:
	CExample() : e(1) { cout << "CExample constructor" << endl; }
	CExample(int x) : e(x) { cout << "CExample constructor" << endl; }
	virtual ~CExample() { cout << "CExample destructor" << endl; }

	int e;
};

void test1()
{
	shared_ptr<CExample> pInt(new CExample());
	cout << (*pInt).e << endl;
	cout << "pInt引用计数:" << pInt.use_count() << endl;

	shared_ptr<CExample> pInt2 = pInt;
	cout << "pInt引用计数:" << pInt.use_count() << endl;
	cout << "pInt2引用计数:" << pInt.use_count() << endl;
}

void test2()
{
	shared_ptr<string> pStr = make_shared<string>(10, 'a');
	cout << *pStr << endl;

	int *p = new int(5);
	shared_ptr<int> pInt(p);
	cout << *pInt << endl;
}

void test3()
{
	shared_ptr<CExample> pInt = make_shared<CExample>(5);
	shared_ptr<CExample> pInt2 = make_shared<CExample>(10);
	cout << "pInt:" << pInt->e << endl;
	cout << "pInt2:" << pInt2->e << endl;

	pInt = pInt2;
	cout << "pInt:" << (*pInt).e << endl;
	cout << "pInt2:" << (*pInt2).e << endl;
}

int main(int argc, char *argv[])
{
	test3();

	getchar();
	return 0;
}