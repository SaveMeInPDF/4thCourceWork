#include "App.h"
#include "cl_2.h"
#include "cl_3.h"
#include "cl_4.h"
#include "cl_5.h"
#include "cl_6.h"
#include <iostream>
#include <string>
#include <stack>

using namespace std;

App::App(Base *parent) : Base(parent) {
}

TYPE_SIGNAL classnum_to_signal(int classnum) {
	switch (classnum) {
		case 1:
			return SIGNAL_D(App::signal);
		case 2:
			return SIGNAL_D(cl_2::signal);
		case 3:
			return SIGNAL_D(cl_3::signal);
		case 4:
			return SIGNAL_D(cl_4::signal);
		case 5:
			return SIGNAL_D(cl_5::signal);
		case 6:
			return SIGNAL_D(cl_6::signal);
	}
	return nullptr;
}

TYPE_HANDLER classnum_to_handler(int classnum) {
	switch (classnum) {
		case 1:
			return HANDLER_D(App::handler);
		case 2:
			return HANDLER_D(cl_2::handler);
		case 3:
			return HANDLER_D(cl_3::handler);
		case 4:
			return HANDLER_D(cl_4::handler);
		case 5:
			return HANDLER_D(cl_5::handler);
		case 6:
			return HANDLER_D(cl_6::handler);
	}
	return nullptr;
}

int App::start() {
	TYPE_SIGNAL signal_f;
	TYPE_HANDLER handler_f;
	this->set_state_branch(1);
	string command, input, message;
	int new_state;
	Base *ptarget;
	Base *pextra;
	this->printtree();
	cin >> command;
	while (command != "END") {
		cin >> input;
		pextra = this->getobject(input);
		if (pextra == nullptr) {
			cout << "\nObject " << input << " not found";
			cin >> input;
			continue;
		}
		if (command == "EMIT") {
			getline(cin, message);//???cin
			int n = pextra->getclassnum();
			pextra->emitsignal(classnum_to_signal(n), message);
		} else if (command == "SET_CONNECT") {
			cin >> input;
			ptarget = this->getobject(input);
			if (ptarget == nullptr) {
				cout << "\nHandler object " << input << " not found";
				continue;
			}
			signal_f = classnum_to_signal(pextra->getclassnum());
			handler_f = classnum_to_handler(ptarget->getclassnum());
			pextra->setconnect(signal_f, ptarget, handler_f);
		} else if (command == "DELETE_CONNECT") {
			cin >> input;
			ptarget = this->getobject(input);
			if (ptarget == nullptr) {
				cout << "\nHandler object " << input << " not found";
				continue;
			}
			signal_f = classnum_to_signal(pextra->getclassnum());
			handler_f = classnum_to_handler(ptarget->getclassnum());
			pextra->removeconnect(signal_f, ptarget, handler_f);
		} else if (command == "SET_CONDITION") {
			cin >> new_state;
			pextra->setstate(new_state);
		}
		cin >> command;
	}
	return 0;
}

int App::getclassnum() {
	return 1;
}

void App::signal(string &message) {
	cout << "\nSignal from " << getpath();
	message += " (class: " + to_string(getclassnum()) + ")";
}

void App::handler(string message) {
	cout << "\nSignal to " << getpath() << " Text: " << message;
}

void App::build() {
	cout << "Object tree";
	string path, child;
	int classnum;
	cin >> child;
	this->setname(child);
	Base *parent_obj;
	Base *current_obj = this;
	cin >> path;
	while (path != "endtree") {
		cin >> child >> classnum;
		parent_obj = current_obj->getobject(path);
		if (parent_obj == nullptr) {
			this->printtree();
			cout << endl << "The head object " << path << " is not found";
			exit(3);
		}
		if (parent_obj->getchild(child) != nullptr) {
			cout << endl << path << " Dubbing the names of subordinate objects";
		} else {
			switch (classnum) {
				case 1:
					current_obj = new App(parent_obj);
					break;
				case 2:
					current_obj = new cl_2(parent_obj, child);
					break;
				case 3:
					current_obj = new cl_3(parent_obj, child);
					break;
				case 4:
					current_obj = new cl_4(parent_obj, child);
					break;
				case 5:
					current_obj = new cl_5(parent_obj, child);
					break;
				case 6:
					current_obj = new cl_6(parent_obj, child);
					break;
			}
		}
		cin >> path;
	}
	Base *target;
	string target_path;
	cin >> path;
	while (path != "end_of_connections") {
		cin >> target_path;
		parent_obj = getobject(path);
		target = getobject(target_path);
		TYPE_SIGNAL signal_f = classnum_to_signal(parent_obj->getclassnum());
		TYPE_HANDLER handler_f = classnum_to_handler(target->getclassnum());
		parent_obj->setconnect(signal_f, target, handler_f);
		cin >> path;
	}
}