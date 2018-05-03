#include <random>
#include <ctime>
#include <iostream>
using namespace std;

void test1()
{
	default_random_engine generator;
	uniform_int_distribution<int> dis(0, 100);
	for (int i = 0; i < 10; ++i)
	{
		cout << dis(generator) << endl;
	}
}

void test2()
{
	default_random_engine e(time(nullptr));
	uniform_int_distribution<int> dis(1, 100);
	for (int i = 0; i < 10; ++i)
	{
		cout << dis(e) << endl;
	}
}

int main(int argc, char *argv[])
{
	test2();

	return 0;
}