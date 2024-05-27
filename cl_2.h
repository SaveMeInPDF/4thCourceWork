#ifndef __CL_2__H
#define __CL_2__H

#include "Base.h"

class cl_2 : public Base {
public:
	cl_2(Base *parent, string name = "cl_obj2");

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif