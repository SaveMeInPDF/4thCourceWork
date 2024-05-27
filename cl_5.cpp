#include "cl_5.h"

cl_5::cl_5(Base *parent, string name) : Base(parent, name) {}

int cl_5::getclassnum() { return 5; }

void cl_5::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void cl_5::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}