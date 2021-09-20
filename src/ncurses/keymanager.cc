#include "driver/ncurses/keymanager.hh"

engine::NCursesKeyManager::NCursesKeyManager(void):
	engine::KeyManager(),
	_dict()
{

	this->_dict["KEY_UP"] = KEY_UP;
	this->_dict["KEY_DOWN"] = KEY_DOWN;
	this->_dict["KEY_LEFT"] = KEY_LEFT;
	this->_dict["KEY_RIGHT"] = KEY_RIGHT;
}

void 		engine::NCursesKeyManager::pushEvent(void) {
	int c = ::getch();
	if (c > 0) {
		std::string ename = this->getEventName(c);

		//engine::NCursesKeyManager::KeyEvent* eventk = new engine::NCursesKeyManager::KeyEvent(ename,c);
		//this->_event_poll.push(eventk);

		this->_event_poll.emplace(ename, c, c);
	}
}

std::string	engine::NCursesKeyManager::getEventName(int v) const {
	auto it = std::find_if(
			this->_dict.begin(),
			this->_dict.end(),
			[v](const auto& m) { return (m.second == v); }
	);

	if (it == this->_dict.end()) {
		std::stringstream sstr;
		sstr << (char)v;
		return (sstr.str());
	}

	return (it->first);
}

