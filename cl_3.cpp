#include "cl_3.h"

cl_3::cl_3(Base *parent, string name) : Base(parent, name) {}

int cl_3::getclassnum() { return 3; }

void cl_3::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void cl_3::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}
