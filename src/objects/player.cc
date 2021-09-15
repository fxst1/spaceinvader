#include "objects/spaceship.hh"

SpaceShip::SpaceShip(engine::Texture *normal, engine::Texture *shield):
	engine::Entity(),
	_pv(5),
	_last_shoot(0)
{
	_shield_recovery = 0;
	_energy = 100;
	_use_shield = false;
	this->setZ(1);

	_player_texture = new SpaceShip::Texture(normal, shield);
	_player_texture->resize(normal->getW(), normal->getH());
	this->resize(normal->getW(), normal->getH());
	this->setTexture(_player_texture);
}
SpaceShip::~SpaceShip(void)
{
	delete _player_texture;
}

void 		SpaceShip::lossPv(engine::Engine & eng) {

	if (_use_shield) {
		_energy -= 10;
	} else {
		_pv--;
	}

	(void)eng;
}

void 		SpaceShip::onDestroy(engine::Engine & engine) {
	(void)engine;
}

std::string		SpaceShip::ID(void) const {
	return (":player");
}
bool			SpaceShip::canOutScene(void) const {
	return (true);
}
void			SpaceShip::onOutScene(engine::Engine & e) {

	if (this->getX() + this->getW() > e.getScene().getW()) {
		this->setX( e.getScene().getW() - this->getW() );
	}

	if (this->getY() + this->getH() > e.getScene().getH()) {
		this->setY( e.getScene().getH() - this->getH() );
	}

	if (this->getX() < 0) {
		this->setX(0);
	}

	if (this->getY() < 0) {
		this->setY(0);
	}

}

bool		SpaceShip::canCollide(engine::Entity const & e) const {
	return (strncmp(e.ID().c_str(), (const char*)":enemy", 6) == 0);
	(void)e;
}

void		SpaceShip::onCollide(engine::Engine & engine, engine::Entity & e) {

	this->lossPv(engine);

	Game*	g = dynamic_cast<Game*>(engine.getGameController());
	g->getHud()->updatePv( _pv );

	if (this->_pv <= 0) {
		engine.removeEntity(this);
	}

	if (e.ID() == ":enemy:bullet") {
		engine.removeEntity(&e);
	} else {

		Wave::EnemyShip* en = dynamic_cast<Wave::EnemyShip*>(&e);
		en->lossPv( engine );

	}

}

void		SpaceShip::tick(engine::Engine & e) {

	Game*	g = dynamic_cast<Game*>( e.getGameController() );
	if (_pv <= 0) {
		g->stop();
		return ;
	}

	if (_use_shield == false) {
		if (_shield_recovery >= 0) {
			_shield_recovery -= e._delta_time;

			if (_shield_recovery <= 0) {
				_energy -= _shield_recovery;
			}
		} else if (_shield_recovery <= 0){
			_energy += 0.5 * e._delta_time;
		}
	} else {
//		_shield_recovery = 500;
	}

	if (_energy < 0) _energy = 0;
	if (_energy > 100) _energy = 100;

	if (_last_shoot >= 0) {
		_last_shoot -= e._delta_time;
	}

	_use_shield = false;


/*
	SDL_Event			event;
	SDL_PollEvent(&event);

	if (event.type == SDL_QUIT) {
		g->stop();
	}
*/
#ifdef SDL_ENGINE

	const std::uint8_t*	keyboard_state_array = SDL_GetKeyboardState(NULL);

	if (keyboard_state_array[SDL_SCANCODE_UP] && !(keyboard_state_array[SDL_SCANCODE_DOWN]))
		this->moveRel(0, -0.9 * e._delta_time);
	else if (!keyboard_state_array[SDL_SCANCODE_UP] && keyboard_state_array[SDL_SCANCODE_DOWN])
		this->moveRel(0, 0.9 * e._delta_time);

	if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !keyboard_state_array[SDL_SCANCODE_LEFT])
		this->moveRel(0.9 * e._delta_time, 0);
	else if (!keyboard_state_array[SDL_SCANCODE_RIGHT] && keyboard_state_array[SDL_SCANCODE_LEFT])
		this->moveRel(-0.9 * e._delta_time, 0);

	if (!keyboard_state_array[SDL_SCANCODE_A] && keyboard_state_array[SDL_SCANCODE_SPACE]) {
		if (_last_shoot <= 0) {
			Factory f(e, this);

			PlayerBullet*	bullet = f.spaceshipBullet(
				this, 1.0, 0
			);
			e.addEntity( bullet );
			_last_shoot = 200;
		}
	}
	else if (keyboard_state_array[SDL_SCANCODE_A] && !keyboard_state_array[SDL_SCANCODE_SPACE]) {

		if (_energy > 0) {
			_use_shield = true;
			_energy -= e._delta_time;
		}

	}
#else

    int c = getch();

	if (c == KEY_UP)
		this->moveRel(0, -0.9 * e._delta_time);
	else if (c == KEY_DOWN)
		this->moveRel(0, 0.9 * e._delta_time);

	if (c == KEY_RIGHT)
		this->moveRel(0.9 * e._delta_time, 0);
	else if (c == KEY_LEFT)
		this->moveRel(-0.9 * e._delta_time, 0);

	if (c == ' ') {
		if (_last_shoot <= 0) {
			Factory f(e, this);

			PlayerBullet*	bullet = f.spaceshipBullet(
				this, 1.0, 0
			);
			e.addEntity( bullet );
			_last_shoot = 200;
		}
	}
	else if (c == 'a') {

		if (_energy > 0) {
			_use_shield = true;
			_energy -= e._delta_time;
		}

	}


#endif
	if (_energy <= 0 && _shield_recovery <= 0) {
		_shield_recovery = 500;
	}

	g->getHud()->updateShield( _energy );

	_player_texture->useShield(_use_shield);
}


/********************/

SpaceShip::Texture::Texture(engine::Texture *normal, engine::Texture *shield):
	engine::Texture(),
	_normal(normal),
	_shield(shield),
	_use_shield(false)
{}
void 	SpaceShip::Texture::useShield(bool on) {
	_use_shield = on;
}
void 	SpaceShip::Texture::render(engine::Box const & dst) {
	_normal->render(dst);
	if (_use_shield) {
		engine::Box dst2 = dst;

		dst2.resize(_shield->getW(), _shield->getH());
		dst2.center(dst);
		_shield->render(dst2);
	}
}
