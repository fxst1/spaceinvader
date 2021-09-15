#include "engine/engine.hh"

engine::GameController::GameController(void):
	_start(false),
	_textures(),
	_engine()
{
	_engine.init();
	_engine.setGameController(this);
}

engine::GameController::~GameController(void)
{}

bool	engine::GameController::isRunning(void) const {
	return (this->_start);
}

void 	engine::GameController::start(void) {
	if (this->_start == false) {
		this->_start = true;
	}
}

void 	engine::GameController::stop(void) {
	if (this->_start == true) {
		this->_start = false;
	}
}

void 	engine::GameController::mainloop(void) {
	this->start();
	this->onStart();

	this->loop();

	this->stop();
}

engine::Texture*    engine::GameController::getTexture(std::string const & name) {
    return (this->_textures[name]);
}