#include "objects/bullet.hh"

Bullet::Bullet(engine::Entity const & parent, std::string const &collide_on, double x_dir, double y_dir):
	_xdir(x_dir),
	_ydir(y_dir),
	_collide_on(collide_on),
	_parent_id(parent.ID())
{}

Bullet::~Bullet(void) {}

std::string	Bullet::ID(void) const {
	return (this->_parent_id + ":bullet");
}

void		Bullet::tick(engine::Engine & e) {
	this->moveRel(
		_xdir * e._delta_time,
		_ydir * e._delta_time
	);
}

void 		Bullet::onDestroy(engine::Engine & e) {
	(void)e;
}

EnemyBullet::EnemyBullet(engine::Entity const & parent, double x_dir, double y_dir):
	Bullet(parent, ":player", x_dir, y_dir) {
}
PlayerBullet::PlayerBullet(engine::Entity const & parent, double x_dir, double y_dir):
	Bullet(parent, ":enemy", x_dir, y_dir) {
}
