#include "objects/factory.hh"

Factory::Factory(engine::Engine & e, engine::Entity *parent, engine::Texture * texture):
	_engine(e),
	_parent(parent),
	_texture(texture)
{
	_game = Factory::getGame(e);
}

Factory::~Factory(void) {}

/****************************************/

Game*			Factory::getGame(engine::Engine & e) {
	return ( dynamic_cast<Game*>(e.getGameController()) );
}
Game*			Factory::getGame(engine::GameController* gc) {
	return ( dynamic_cast<Game*>(gc) );
}

/****************************************/

PlayerBullet*			Factory::spaceshipBullet(engine::Entity * parent, double x_dir, double y_dir) {
	PlayerBullet*		b = new PlayerBullet(*_parent, x_dir, y_dir);
	b->setTexture(_game->_textures["bullet"]);
	b->setZ(1);
	b->resize( b->getTexture()->getW(), b->getTexture()->getH() );
	b->center(*parent);
	return (b);
}

EnemyBullet*			Factory::enemyBullet(engine::Entity * parent, double x_dir, double y_dir) {
	EnemyBullet*		b = new EnemyBullet(*_parent, -x_dir, y_dir);
	b->setTexture(_game->_textures["bullet2"]);
	b->setZ(1);
	b->resize( b->getTexture()->getW(), b->getTexture()->getH() );
	b->center(*parent);
	return (b);
}

ExplosionEntity*		Factory::explosion(engine::Entity * parent) {
	ExplosionEntity*	ex = new ExplosionEntity(_game, *parent);
	ex->setZ(0);
	return (ex);
}
Wave*					Factory::wave(std::size_t n_enemies, MoveFunc * f) {
	Wave*			w = new Wave(n_enemies, f);
	w->setZ(1);
	return (w);
}
