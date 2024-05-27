#include "cl_4.h"

cl_4::cl_4(Base *parent, string name) : Base(parent, name) {}

int cl_4::getclassnum() { return 4; }

void cl_4::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void cl_4::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}
