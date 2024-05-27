#ifndef __CL_4__H
#define __CL_4__H

#include "Base.h"

class cl_4 : public Base {
public:
	cl_4(Base *parent, string name = "cl_obj4");

	int getclassnum();

	void signal(string &message);

	void handler(string message);
};

#endif
