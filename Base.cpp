#include "Base.h"
#include <stack>
#include <queue>

Base::Base(Base *parent, string name) {
	this->name = name;
	this->parent = parent;
	if (parent) {
		parent->children.push_back(this);
	}
}

bool Base::setname(string name) {
	this->name = name;
	return true;
}

string Base::getname() { return this->name; }

Base *Base::getparent() { return this->parent; }

Base *Base::getchild(string name) {
	for (auto child: this->children) {
		if (child->getname() == name) return child;
	}
	return nullptr;
}

Base *Base::searchbranch(string name) {
	Base *found = nullptr;
	queue<Base *> elementsqueue;
	elementsqueue.push(this);
	while (!elementsqueue.empty()) {
		Base *elem = elementsqueue.front();
		elementsqueue.pop();
		if (elem->name == name) {
			if (found != nullptr) {
				return nullptr;
			} else {
				found = elem;
			}
		}
		for (auto i: elem->children) {
			elementsqueue.push(i);
		}
	}
	return found;
}

Base *Base::searchtree(string name) {
	if (parent != nullptr) {
		return parent->searchtree(name);
	} else {
		return searchbranch(name);
	}
}

void Base::printttree() {
	Base *root = this;
	while (root->getparent()) {
		cout << " ";
		root = root->getparent();
	}
	cout << this->getname() << "\n";
	for (auto child: this->children)
		child->printtree();
}

void Base::printstate() {
	Base *root = this;
	bool ready = this->state != 0;
	while (root->getparent()) {
		cout << " ";
		root = root->getparent();
		if (root->state == 0) ready = false;
	}
	cout << this->getname() << (ready ? " is ready" : " is not ready");
	for (auto child: this->children) {
		cout << "\n";
		child->printstate();
	}
}

void Base::setstate(int state) {
	bool parentsready = true;
	Base *root = this;
	while (root->getparent()) {
		root = root->getparent();
		if (root->state == 0) {
			parentsready = false;
			break;
		}
	}
	if (parentsready) {
		this->state = state;
		if (state != 0) return;
	}
	for (auto child: this->children) {
		child->state = 0;
		if (!child->children.empty()) child->setstate(0);
	}
}

//------------------------------------------------------КВ3
bool Base::setparent(Base *parent_new) {
	if (parent == nullptr) {
		return false;
	}
	if (parent_new == nullptr) {
		return false;
	}
	if (parent_new->getchild(this->name) != nullptr) {
		return false;
	}
	stack<Base *> stack;
	stack.push(this);
	while (!stack.empty()) {
		Base *current_node = stack.top();
		stack.pop();
		if (current_node == parent_new) {
			return false;
		}
		for (auto i: current_node->children) {
			stack.push(i);
		}
	}
	int temp = 0;
	for (int i = 0; i < parent->children.size(); i++) {
		if (parent->children[i] == this) {
			temp = i;
		}
	}
	auto iteration = parent->children.cbegin();//Base~auto
	parent->children.erase(iteration + temp);
	this->parent = parent_new;
	parent_new->children.push_back(this);
	return true;
}

void Base::removechild(const string &child_name) {
	int temp = 0;
	for (int i = 0; i < children.size(); i++) {
		if (children[i]->getname() == child_name) {
			auto iteration = children.cbegin();
			delete children[i];
			children.erase(iteration + i);
		}
	}
}

Base *Base::getobject(string path) {
	if (path.empty()) {
		return nullptr;
	}
	if (path == ".") {
		return this;
	}
	if (path[0] == '.') {
		return this->searchbranch(path.substr(1));//?????
	}
	if (path.find("//") != std::string::npos) {
		return this->searchtree(path.substr(2));
	}
	if (path[0] != '/') {
		size_t slash = path.find('/');
		Base *pchild = this->getchild(path.substr(0, slash));
		if (pchild == nullptr || slash == std::string::npos) {
			return pchild;
		}
		return pchild->getobject(path.substr(slash + 1));
	}
	Base *proot = this;
	while (proot->getparent() != nullptr) {
		proot = proot->getparent();
	}
	if (path == "/") {
		return proot;
	}
	return proot->getobject(path.substr(1));
}

void Base::printtree(int level) {
	cout << endl;
	for (int i = 0; i < level; ++i) {
		cout << " ";
	}
	cout << this->getname();
	for (int i = 0; i < children.size(); ++i) {
		children[i]->printtree(level + 1);
	}
}

//--------------------------КВ4--------------------
void Base::setconnect(TYPE_SIGNAL signal, Base *target,
					  TYPE_HANDLER handler) {
	for (auto &connect: connects) {
		if (connect->signal == signal && connect->target == target &&
			connect->handler == handler)
			return;
	}
	auto *new_connect = new connect();
	new_connect->signal = signal;
	new_connect->target = target;
	new_connect->handler = handler;
	connects.push_back(new_connect);
}

void Base::removeconnect(TYPE_SIGNAL signal, Base *target,
						 TYPE_HANDLER handler) {
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->signal == signal && connects[i]->target == target &&
			connects[i]->handler == handler) {
			delete connects[i];
			connects.erase(connects.begin() + i);
			return;
		}
	}
}

void Base::emitsignal(TYPE_SIGNAL signal, string &cmd) {
	if (this->state == 0)
		return;
	(this->*signal)(cmd);
	for (int i = 0; i < connects.size(); i++) {
		if (connects[i]->signal == signal) {
			TYPE_HANDLER handler = connects[i]->handler;
			Base *target = connects[i]->target;
			if (target->state != 0)
				(target->*handler)(cmd);
		}
	}
}

string Base::getpath() {
	string result;
	stack<string> stck;
	Base *root = this;
	while (root->getparent() != nullptr) {
		stck.push(root->getname());
		root = root->getparent();
	}
	while (!stck.empty()) {
		result += '/' + stck.top();
		stck.pop();
	}
	if (result.empty())
		return "/";
	return result;
}

int Base::getclassnum() { return 0; }

void Base::set_state_branch(int new_state) {
	if (getparent() != nullptr && getparent()->state == 0) return;
	setstate(new_state);
	for (auto &i: children)
		i->set_state_branch(new_state);
}