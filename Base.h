#ifndef __BASE__H
#define __BASE__H

#include <string>
#include <vector>
#include <iostream>

#define SIGNAL_D(signal_f)(TYPE_SIGNAL)(&signal_f)
#define HANDLER_D(handler_f)(TYPE_HANDLER)(&handler_f)
using namespace std;

class Base;

typedef void(Base::*TYPE_SIGNAL)(string &);

typedef void(Base::*TYPE_HANDLER)(string);

class Base {
//КВ_1
	string name;
	Base *parent = nullptr;
	vector<Base *> children;
//КВ_2
	int state = 0;
//КВ_4
	struct connect {
		TYPE_SIGNAL signal;
		Base *target;
		TYPE_HANDLER handler;
	};
	vector<connect *> connects;
public:
//КВ_1
	Base(Base *parent, string name = "Base");

	bool setname(string name);

	string getname();

	Base *getparent();

	Base *getchild(string name);

//КВ2
	Base *searchbranch(string name);

	Base *searchtree(string name);

	void printttree();

	void printtree(int level = 0);

	void printstate();

	void setstate(int state);

//КВ3
	bool setparent(Base *parent_new);

	void removechild(const string &name);

	Base *getobject(string path);

//КВ4
	void setconnect(TYPE_SIGNAL signalptr, Base *targetptr, TYPE_HANDLER handlerptr);

	void removeconnect(TYPE_SIGNAL signalptr, Base *targetptr, TYPE_HANDLER handlerptr);

	void emitsignal(TYPE_SIGNAL signalptr, string &command);

	string getpath();

	virtual int getclassnum();

	void set_state_branch(int newstate);
};

#endif
