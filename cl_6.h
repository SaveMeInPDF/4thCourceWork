#ifndef __CL_6__H
#define __CL_6__H

#include "Base.h"

class cl_6 : public Base {
public:
	cl_6(Base *parent, string name = "cl_obj6");

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif
