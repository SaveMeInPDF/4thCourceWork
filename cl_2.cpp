#include "cl_2.h"

cl_2::cl_2(Base *parent, string name) : Base(parent, name) {}

int cl_2::getclassnum() { return 2; }

void cl_2::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void cl_2::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}
