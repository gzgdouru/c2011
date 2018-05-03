#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>
#include <ratio>
#include <sstream>
#include <ctime>
using namespace std;

void test1()
{
	cout << "hello" << endl;
	this_thread::sleep_for(chrono::seconds(2));
	cout << "hi" << endl;
	this_thread::sleep_for(chrono::milliseconds(1000));
	cout << "bye" << endl;

	chrono::minutes min(10);
	chrono::seconds sec(21);
	chrono::seconds diff = min - sec;
	cout << "diff:" << diff.count() << " seconds." << endl;
	cout << "diff:" << chrono::duration_cast<chrono::minutes>(diff).count() << " minutes." << endl;
}

void test2()
{
	typedef chrono::duration<int, ratio<60 * 60 * 24>> days;
	chrono::time_point<chrono::system_clock, days> today = chrono::time_point_cast<days>(chrono::system_clock::now());
	cout << today.time_since_epoch().count() << " days" << endl;

	chrono::system_clock::time_point now = chrono::system_clock::now();
	time_t last = chrono::system_clock::to_time_t(now - chrono::hours(24));
	time_t next = chrono::system_clock::to_time_t(now + chrono::hours(24));

	cout << put_time(localtime(&last), "%F %T") << endl;
	cout << put_time(localtime(&next), "%F %T") << endl;
}

void test3()
{
	chrono::steady_clock::time_point before = chrono::steady_clock::now();
	cout << "hello" << endl;
	this_thread::sleep_for(chrono::microseconds(100));
	chrono::steady_clock::time_point after = chrono::steady_clock::now();
	cout << "diff:" << (after - before).count() << " ticks" << endl;
	cout << "diff:" << chrono::duration_cast<chrono::microseconds>(after - before).count() << " microseconds" << endl;
	cout << "diff:" << chrono::duration_cast<chrono::milliseconds>(after - before).count() << " milliseconds" << endl;

	chrono::system_clock::time_point now = chrono::system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	cout << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S") << endl;
}

//duration 表示一段时间
void test4()
{
	typedef chrono::duration<int> seconds_type;
	typedef chrono::duration<int, milli> milliseconds_type;
	typedef chrono::duration<int, ratio<60 * 60>> hours_type;
	
	hours_type h_oneday(24);	// 24h
	seconds_type s_oneday(24 * 3600);
	milliseconds_type ms_oneday(s_oneday);

	seconds_type s_oneHours(60 * 60);
	hours_type h_oneHours(chrono::duration_cast<hours_type>(s_oneHours));
	milliseconds_type ms_oneHours(s_oneHours);

	cout << ms_oneHours.count() << " ms in 1h" << endl;
}

//duration 表示一段时间
void test5()
{
	chrono::milliseconds foo(1000);
	foo *= 60;

	cout << "duration(in periods): " << foo.count() << " milliseconds." << endl;	
	cout << "duration(in seconds):" << foo.count() * chrono::milliseconds::period::num / chrono::milliseconds::period::den << " seconds." << endl;
}

//time_point 表示一个具体时间
void test6()
{
	chrono::system_clock::time_point tp_epoch;
	chrono::time_point<chrono::system_clock, chrono::duration<int>> tp_seconds(chrono::duration<int>(1));
	chrono::system_clock::time_point tp(tp_seconds);

	cout << "1 seconds since system_clock epoch = "
		<< tp.time_since_epoch().count() << " system_clock periods." << endl;

	time_t tt = chrono::system_clock::to_time_t(tp);
	cout << "time_point tp is: " << ctime(&tt) << endl;
}

// 获取从1970年1月1日到现在经过了多少天
void test7()
{
	typedef chrono::duration<int, ratio<60 * 60 * 24>> days_type;
	chrono::time_point<chrono::system_clock, days_type> today = chrono::time_point_cast<days_type>(chrono::system_clock::now());
	cout << today.time_since_epoch().count() << " days since epoch." << endl;
}

//system::clock
void test8()
{
	using namespace std::chrono;
	duration<int, ratio<60 * 60 * 24>> one_day(1);
	
	system_clock::time_point today = system_clock::now();
	system_clock::time_point tomorrow = today + one_day;

	time_t tt;
	tt = system_clock::to_time_t(today);
	cout << "today is: " << ctime(&tt) << endl;

	tt = system_clock::to_time_t(tomorrow);
	cout << "tomorrow will be: " << ctime(&tt) << endl;
}

//为了表示稳定的时间间隔，后一次调用now()得到的时间总是比前一次的值大（这句话的意思其实是，如果中途修改了系统时间，也不影响now()的结果），每次tick都保证过了稳定的时间间隔
void test9()
{
	using namespace std::chrono;
	steady_clock::time_point t1 = steady_clock::now();
	cout << "printing out 1000 stars....\n";
	for (int i = 0; i < 1000; ++i)
	{
		cout << "*";
	}
	cout << endl;

	steady_clock::time_point t2 = steady_clock::now();
	duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
	cout << "it took me " << time_span.count() << " seconds." << endl;
}

//格式化
void test10()
{
	using namespace std::chrono;
	system_clock::time_point now = system_clock::now();
	time_t t = chrono::system_clock::to_time_t(now);
	stringstream ss;
	ss << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S");
	cout << ss.str() << endl;

	tm t3;
	int year, month, day, hour, minute, second;
	sscanf(ss.str().c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
	t3.tm_year = year - 1900;
	t3.tm_mon = month - 1;
	t3.tm_mday = day;
	t3.tm_hour = hour;
	t3.tm_min = minute;
	t3.tm_sec = second;
	t3.tm_isdst = 0;

	std::get_time(&t3, "%b %d %Y %H:%M:%S");
	cout << t3.tm_mon + 1 << endl;
	system_clock::time_point now2 = system_clock::from_time_t(mktime(&t3));	
	t = system_clock::to_time_t(now2);
	cout << put_time(localtime(&t), "%Y-%m-%d %H:%M:%S") << endl;
}

int main(int argc, char *argv[])
{
	test10();

	getchar();
	return 0;
}
