#ifndef __CL_5__H
#define __CL_5__H

#include "Base.h"

class cl_5 : public Base {
public:
	cl_5(Base *parent, string name = "cl_obj5");

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif