#include "engine/keymanager.hh"

engine::KeyManager::KeyEvent::KeyEvent(void):
	_name("undefined"),
	_value(0),
	_code(0)
{}

engine::KeyManager::KeyEvent::KeyEvent(std::string const &name, int value, int code):
	_name(name),
	_value(value),
	_code(code)
{}

engine::KeyManager::KeyEvent::KeyEvent(engine::KeyManager::KeyEvent const &src):
	_name(src._name),
	_value(src._value),
	_code(src._code)
{}

engine::KeyManager::KeyEvent::~KeyEvent(void)
{}

engine::KeyManager::KeyEvent&		engine::KeyManager::KeyEvent::operator=(engine::KeyManager::KeyEvent const &src) {

	if (&src != this) {
		this->_name = src._name;
		this->_value = src._value;
		this->_code = src._code;		
	}

	return (*this);
}

std::string const &			engine::KeyManager::KeyEvent::getName(void) const {
	return (this->_name);
}

/*************************************************************************************/

engine::KeyManager::KeyManager(void):
	_keymanager(),
	_event_poll()
{}

engine::KeyManager::~KeyManager(void)
{}

void		engine::KeyManager::mapkey(std::string const &name, int driver_value) {
	(void) name;
	(void) driver_value;
}

bool		engine::KeyManager::poll(void) {
	if (!this->_event_poll.empty()) {
		this->onKey(
			this->_event_poll.back()
		);
		this->_event_poll.pop();
		return (true);
	}
	return (false);
}
