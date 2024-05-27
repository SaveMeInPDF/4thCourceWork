#include "cl_6.h"

cl_6::cl_6(Base *parent, string name) : Base(parent, name) {}

int cl_6::getclassnum() { return 6; }

void cl_6::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void cl_6::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}
