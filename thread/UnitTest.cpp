#include <iostream>
#include <thread>
#include <atomic>
#include <string>
using namespace std;

atomic_llong sum = 0;

void add(int)
{
	for (int i = 1; i < 100001; ++i)
	{
		sum += i;
	}
}

void testOne()
{
	thread th1(add, 0);
	thread th2(add, 0);

	th1.join();
	th2.join();

	cout << "sum:" << sum << endl;
}

class CPrint
{
public:
	CPrint() {}
	void print(const string &szMsg)
	{
		while (true)
		{
			cout << this_thread::get_id() << ":" << szMsg << endl;
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
	}

	void run()
	{
		while (true)
		{
			thread *t1 = new thread(&CPrint::print, this, "hello world");
			this_thread::sleep_for(chrono::milliseconds(2000));
		}
	}
};

int main(int argc, char *argv[])
{
	//testOne();
	CPrint pp;
	pp.run();

	getchar();
	return 0;
}