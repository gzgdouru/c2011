#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
using namespace std;

void func(int &x, int y, int z)
{
	x = y * z + x;
	cout << x << " ";
}

void testOne()
{
	vector<int> vtInt = { 5, 4, 3, 2, 1 };
	int a = 2, b = 1;

	for_each(vtInt.begin(), vtInt.end(), [b](int &x) {
		cout << x + b << " ";
	});
	cout << endl;

	for_each(vtInt.begin(), vtInt.end(), [=](int &x) {
		x = a * b + x;
		cout << x << " ";
	});
	cout << endl;

	for_each(vtInt.begin(), vtInt.end(), [=](int &x) ->int{
		return x * 2;
	});
	for (auto it : vtInt)
	{
		cout << it << " ";
	}
	cout << endl;

	function<void(int&)> f = bind(func, placeholders::_1, a, b);
	for_each(vtInt.begin(), vtInt.end(), f);
	cout << endl;
}

int main(int argc, char *argv[])
{
	testOne();

	getchar();
	return 0;
}