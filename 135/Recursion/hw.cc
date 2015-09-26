/* Team Penguin */
/* Eric Wong, Kimmi White, Nick Onze, Robert Rico */
/* ericwong@csus.edu, kawhite9@yahoo.com nwantz@gmail.com*/
/* gordonvs@ecs.csus.edu */

#include <cstdlib>
#include <iostream>

using namespace std;
int story(int base,string animals[],string attr[]);
string animals[6] = {"Girl","Cat","Elephant","Moose","Goose","Sandwich"};
string pronoun[6] = {"She","He","She","She","He","He"};
string attr[6] = {"Big Red Blanket","Long Tail","Long Trunk","Big Horns","Large Beak","Tomato"};
string sleepy[6] = {"Not","Kinda","Semi","Exremely","Very","Dead"};

int main()
{
	cout << "Once upon a time..." << endl;
	story(0,animals,attr);
}

int story(int base,string animals[],string attr[])
{
	if(base == 6)
		return 0;

	cout << "There was a "+animals[base]+" and "+pronoun[base]+" had "+attr[base] << endl;
	cout << pronoun[base]+" was "+sleepy[base]+" sleepy." << endl;

	if(base == 5)
		cout << "And then..." << endl;

	story(base+1,animals,attr);
	cout << "The "+animals[base]+" slept." << endl;
}
