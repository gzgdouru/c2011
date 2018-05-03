#include "../../protobuf/cpp/addressbook.pb.h"
#include <iostream>
#include "tutorial.pb.h"
using namespace std;

//void test1()
//{
//	addressbook::AddressBook person;
//	addressbook::Person *pi = person.add_person_info();
//	pi->set_name("aut");
//	pi->set_id(1219);
//	cout << "before clear(), id = " << pi->id() << endl;
//	pi->clear_id();
//	cout << "after clear(), id = " << pi->id() << endl;
//}

void test2()
{
	ouru::ouruTest person;

	person.set_name("flamingo");
	person.set_age(18);
	cout << person.name() << endl;
	cout << person.age() << endl;

}

int main(int argc, char *argv[])
{
	test2();

	getchar();
	return 0;
}