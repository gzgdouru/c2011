#include <iostream>
#include <future>
#include "boost/asio.hpp"
#include "boost/thread.hpp"
using namespace std;

void testOne()
{
	future<int> f1 = async(launch::async, []() {
		return 8;
	});

	cout << f1.get() << endl;

	future<void> f2 = async(launch::async, []() {
		this_thread::sleep_for(std::chrono::seconds(5));
		cout << 8 << endl;
	});
	f2.get();

	cout << "hello" << endl;

	future<int> f3 = async(launch::async, []() {
		this_thread::sleep_for(std::chrono::seconds(3));
		return 8;
	});

	cout << "waiting..." << endl;
	future_status status;
	do
	{
		status = f3.wait_for(chrono::seconds(5));
		if (status == future_status::deferred)
		{
			cout << "deferred" << endl;
		}
		else if (status == future_status::timeout)
		{
			cout << "timeout" << endl;
		}
		else if (status == future_status::ready)
		{
			cout << "ready" << endl;
		}
	} while (status != future_status::ready);

	cout << f3.get() << endl;
}

void print()
{
	for (int i = 0; i < 10000000000; ++i)
	{
	//	cout << "hello : " << i << endl;
	//	this_thread::sleep_for(chrono::seconds(1));
	}
}

void testTwo()
{
//	async(bind(print, placeholders::_1));
	future<void> fut = async(print);

	cout << "standby exit..." << endl;
	this_thread::sleep_for(chrono::seconds(5));

	cout << "exit" << endl;
	fut.wait();
}

bool is_prime(int x)
{
	for (int i = 2; i < x; ++i)
	{
		if (x % i == 0)
			return false;
	}

	return true;
}

void testThree()
{
	future<bool> fut = async(is_prime, 444444443);

	cout << "checking, please wait";
	/*while (fut.wait_for(chrono::milliseconds(100)) == future_status::timeout)
	{
		cout << ".";
	}
	cout << endl;

	bool x = fut.get();
	cout << "444444443 " << (x ? "is" : "is not") << " prime" << endl;*/
}

void testFour()
{
	using namespace boost;
	for (int i = 0; i < 5; ++i)
	{
		boost::async([i]() {
			for (int j = 0; j < 10; ++j)
			{
				cout << i << "hello..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
		});
	}
}

void testFive()
{
	for (int i = 0; i < 5; ++i)
	{
		std::async(launch::async, [i]() {
			for (int j = 0; j < 10; ++j)
			{
				cout <<  i << " hello..." << endl;
				std::this_thread::sleep_for(std::chrono::milliseconds(3000));
			}
		});
	}
}

void printHello()
{
	for (int i = 0; i < 10; ++i)
	{
		cout << std::this_thread::get_id() << ":" << i << " hello..." << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(3000));
	}
}

void testSix()
{
	for (int i = 0; i < 5; ++i)
	{
		std::thread *pth1 = new std::thread(printHello);
	}
}

void test_7()
{
	vector<int> vtInt;
	auto w = async(launch::async, [&] {
		int i = 0;
		while (true)
		{
			if (i == 10)
			{
				vtInt.push_back(i);
				i = 0;
			}
			++i;
			this_thread::sleep_for(chrono::seconds(1));
		}
	});


	while (true)
	{
		cout << "vector size:" << vtInt.size() << endl;
		this_thread::sleep_for(chrono::seconds(1));
	}
}

int main(int argc, char *argv[])
{
	testOne();
	getchar();
	return 0;
}