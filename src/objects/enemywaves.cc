#include "spaceinvader.hh"
#include "gameobjects.hh"

Wave::EnemyShip::EnemyShip(Wave* w):
	engine::Entity(),
	_group(w),
	_pv(3),
	_last_shoot(0),
	_recovery(500),
	_move_func(nullptr)
{
	std::cout << "* Alloc ship without call move" << std::endl;
}
Wave::EnemyShip::EnemyShip(Wave* w, MoveFunc *mvfunc):
	engine::Entity(),
	_group(w),
	_pv(3),
	_last_shoot(0),
	_recovery(500),
	_move_func(mvfunc)
{
	std::cout << "* Alloc ship with call move" << std::endl;
}
Wave::EnemyShip::~EnemyShip(void) {
	if (_move_func) delete _move_func;
}

void 		Wave::EnemyShip::lossPv(engine::Engine & eng) {
	_pv--;
	(void)eng;
}

std::string	Wave::EnemyShip::ID(void) const {
	return (":enemy");
}

bool	Wave::EnemyShip::canOutScene(void) const {
	return (false);
}

void	Wave::EnemyShip::onInit(engine::Engine & e) {
	(void)e;
}
void	Wave::EnemyShip::tick(engine::Engine & e) {

	if (this->_pv <= 0 || this->getX() < -100) {
		e.removeEntity(this);
	} else {

		engine::Box		old_pos = *this;

		this->moveTick(e);

		if (_last_shoot > 0) _last_shoot -= e._delta_time;
		if (_last_shoot <= 0) {
			this->shoot(e, old_pos);
		}

	}

}

void 	Wave::EnemyShip::populateBullet(engine::Engine & e) {

	Factory			f(e, this);
	EnemyBullet*	bullet = f.enemyBullet( this, 1.0, 0 );
	bullet->setX(this->getX());
	e.addEntity( bullet );

	_last_shoot = _recovery;
}

void 	Wave::EnemyShip::moveTick(engine::Engine & e) {
	if (_move_func == nullptr) {
		this->_group->moveFunc(this, e);
	}
	else {
		(*this->_move_func)(this, e);
	}
}

void 	Wave::EnemyShip::shoot(engine::Engine & e, engine::Box const &oldpos) {

	if (_last_shoot <= 0 && oldpos.getX() >= 400 && oldpos.getY() < this->getY()) {
		this->populateBullet(e);
	}

}

void 	Wave::EnemyShip::onDestroy(engine::Engine & e) {
	this->_group->remove(this, e);

	Factory		f(e, this);
	e.addEntity(
		f.explosion(this)
	);
}

bool	Wave::EnemyShip::canCollide(engine::Entity const & e) const {
	return (e.ID() == ":player:bullet");
}

void	Wave::EnemyShip::onCollide(engine::Engine & engine, engine::Entity & e) {
	if (this->_pv > 0) this->_pv--;

	if (e.ID() == ":player:bullet") {
		engine.removeEntity( &e );
	}

	(void)engine;
	(void)e;
}

/*********************/

Wave::Wave(std::size_t n, MoveFunc * mv):
	engine::Entity(),
	_n_ennemies(n),
	_enemies(),
	_move_func(mv)
{}
Wave::~Wave(void) {
	//delete _move_func;
}

void 	Wave::remove(Wave::EnemyShip *en, engine::Engine & e) {
	this->_enemies.remove(en);
	if (this->_enemies.size() == 0) {
		e.removeEntity(this);
	}
}

bool	Wave::isEmpty(void) const {
	return (this->_enemies.size() == 0);
}

void	Wave::populate(engine::Engine & e, Game &g) {
	Wave::EnemyShip*	prev_en = nullptr;
	for (std::size_t i = 0; i < _n_ennemies; i++) {

		Wave::EnemyShip*	en = new Wave::EnemyShip(this);
		en->setTexture( g._textures["spider"] );
		en->resize(en->getTexture()->getW(), en->getTexture()->getH());
		en->setZ(1);
		if (prev_en == nullptr) {
			en->move(
				(int)e.getScene().getW(),
				(int)(e.getScene().getH() / 2) - (en->getH() / 2)
			);
		}
		else {
			en->move(prev_en->getX() - 100, prev_en->getY());
		}

		prev_en = en;
		this->_enemies.push_back(en);
		e.addEntity(en);
	}
}

bool	Wave::canOutScene(void) const {
	return (true);
}
void 	Wave::onOutScene(engine::Engine & e) {
	(void)e;
}
bool	Wave::canCollide(engine::Entity const & e) const {
	return (false);
	(void)e;
}
void 	Wave::onDestroy(engine::Engine & e) {
	(void)e;
}

void 	Wave::moveFunc(engine::Entity * ent, engine::Engine & eng) {
	if (this->_move_func != nullptr)
		(*this->_move_func)(ent, eng);
}
