#ifndef __APP__H
#define __APP__H

#include "Base.h"

class App : public Base {
public:
	App(Base *parent);

	void build();

	int start();

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif