#include "engine/engine.hh"

engine::Engine::Engine(void) :
	engine::Values(),
	_background(),
	_objects(),
	_garbage(),
	_loaded(),
	_log()
{
	_log.open("engine.log", std::ofstream::out | std::ofstream::trunc);
}

engine::Engine::~Engine(void) {
	_log.close();
}

void	engine::Engine::init(void) {
	_log << "---- INITIALIZED ----" << std::endl;
	this->_objects.clear();
}

void	engine::Engine::addEntity(engine::Entity *e) {

	if (e == nullptr) return;

	auto it = std::find(this->_loaded.begin(), this->_loaded.end(), e);
	if (it == this->_loaded.end()) {
		_log << "Add Entity " << e->ID() << std::endl;
		this->_loaded.insert(e);
	}
}

void	engine::Engine::removeEntity(engine::Entity *e) {

	if (e == nullptr) return;

	auto it = std::find(this->_garbage.begin(), this->_garbage.end(), e);
	if (it == this->_garbage.end()) {
		_log << "Delete Entity " << e->ID() << std::endl;

		e->onDestroy(*this);
		this->_garbage.insert(e);
	}
}

void	engine::Engine::setGameController(engine::GameController* controller) {
	_log << "* A game controller has been setted" << std::endl;
	this->_game = controller;
}
engine::GameController*	engine::Engine::getGameController(void) {
	return (this->_game);
}

engine::Box&		engine::Engine::getScene(void) {
	return (this->_scene);
}

engine::Box&		engine::Engine::getCamera(void) {
	return (this->_camera);
}

double	engine::Engine::getDeltaTime(double factor) const {
	double tmp = this->_delta_time * factor;
	if (((int)tmp) == 0) {
		return (1);
	} else
		return (tmp);
}

void	engine::Engine::tick(void) {

	//_log << "* TICK [" << std::dec << this->getTimer() << "]" << std::endl;

	// Clear all old entities
	for (engine::Entity* e: _garbage) {
		auto it = this->_objects.find(e);
		if (it != this->_objects.end()) {
			_objects.erase( it );
		}
		delete e;
	}
	_garbage.clear();

	// Append all new entities
	for (engine::Entity* e: _loaded) {
		auto it = this->_objects.find(e);
		if (it == this->_objects.end()) {
			_objects.insert( e );
		}
	}
	_loaded.clear();

	//std::size_t							index = 0;
	std::multimap<int, engine::Entity*>	printer;
	for (engine::Entity* e: this->_objects) {

		e->tick(*this);

		if (e->canOutScene() && !this->getScene().in( *e ) ) {
			e->onOutScene(*this);
		}

		if (e->getZ() >= 0) {

			auto it = this->_objects.begin();
			auto it_end = this->_objects.end();

			//std::advance(it, index + 1);

			for (; it != it_end; ++it) {

				engine::Entity*	e2 = *it;

				if (e2->getZ() < 0) {
					continue;
				}

				if (e->canCollide(*e2)) {
					this->overlay(e, e2);
				}

			}

		}

		//index++;

		if (e->getTexture() != nullptr) {
			printer.insert({e->getZ(), e});
		}
	}

	this->_game->onPreRender();
	std::for_each(printer.begin(), printer.end(), [&](const auto& n) {
		n.second->getTexture()->render(*n.second);
	});
	this->_game->onPostRender();
}

bool	engine::Engine::overlay( engine::Entity *a, engine::Entity *b ) {

	bool	a_in_b = a->over(*b);
/*
	this->_log << "Test collide: " << (a_in_b ? " yes" : " no") << std::endl;
	this->_log << "A: " << a->ID() << *a << std::endl;
	this->_log << "B: " << b->ID() << *b << std::endl;
*/

	if (a_in_b) {
		a->onCollide(*this, *b);
		b->onCollide(*this, *a);
	}
	return (a_in_b);
}
