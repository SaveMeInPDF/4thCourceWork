#ifndef __CL_3__H
#define __CL_3__H

#include "Base.h"

class cl_3 : public Base {
public:
	cl_3(Base *parent, string name = "cl_obj3");

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif
