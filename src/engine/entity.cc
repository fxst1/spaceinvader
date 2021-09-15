#include "engine/entity.hh"
#include "engine/engine.hh"

engine::Entity::Entity(void):
	engine::Box(),
	engine::Values(),
	_texture(nullptr)
{}

engine::Entity::~Entity(void){}

void	engine::Entity::setTexture(engine::Texture * texture) {
	this->_texture = texture;
}
engine::Texture*	engine::Entity::getTexture(void) {
	return (this->_texture);
}

std::string	engine::Entity::ID(void) const {
	return (":_");
}

bool		engine::Entity::canCollide(engine::Entity const & e) const {
	return (false);
	(void)e;
}

void		engine::Entity::onCollide(engine::Engine & engine, engine::Entity & e) {
	(void)engine;
	(void)e;
}

bool		engine::Entity::canOutScene(void) const {
	return (false);
}

void		engine::Entity::onOutScene(engine::Engine & engine) {
	(void)engine;
}

void		engine::Entity::onDestroy(engine::Engine & engine) {
	(void)engine;
}

void		engine::Entity::tick(engine::Engine & engine) {
	engine::Values::tick(engine._delta_time);
	(void)engine;
}

/**************************************/
engine::Values::Values(void):
	_speed(1.0),
	_timer(0),
	_maxtimer(1000000)
{}

engine::Values::Values(engine::speed_t speed, engine::timer_t maxframe):
	_speed(speed),
	_timer(0),
	_maxtimer(maxframe)
{}

engine::Values::~Values(void) {}


void		engine::Values::tick(long delta_time) {
	if (this->_maxtimer != 0) {
		this->_timer = (this->_timer + delta_time) % this->_maxtimer;
	} else
		this->_timer += delta_time;
}

void				engine::Values::setSpeed(engine::speed_t speed) {
	this->_speed = speed;
}
engine::speed_t		engine::Values::getSpeed(void) const {
	return (this->_speed);
}

void				engine::Values::setTimer(engine::timer_t timer) {
	this->_timer = timer;
}
engine::timer_t		engine::Values::getTimer(void) const {
	return (this->_timer);
}

void				engine::Values::setMaxTimer(engine::timer_t timer) {
	this->_maxtimer = timer;
}
engine::timer_t		engine::Values::getMaxTimer(void) const {
	return (this->_maxtimer);
}
