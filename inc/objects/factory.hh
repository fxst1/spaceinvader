#ifndef SPACEINVADER_FACTORY_HH
# define SPACEINVADER_FACTORY_HH
# include "gameobjects.hh"

class	Factory {

	private:

		Game*				_game;
		engine::Engine&		_engine;
		engine::Entity*		_parent;
		engine::Texture*	_texture;

		static Game*	getGame(engine::Engine & e);
		static Game*	getGame(engine::GameController * e);

	public:

		Factory(engine::Engine & e, engine::Entity* entity, engine::Texture * texture = nullptr);
		~Factory(void);

		engine::Entity*		spaceship(void);
		PlayerBullet*		spaceshipBullet(engine::Entity * parent, double x_dir, double y_dir);
		EnemyBullet*		enemyBullet(engine::Entity * parent, double x_dir, double y_dir);
		ExplosionEntity*	explosion(engine::Entity * parent);
		Wave*				wave(std::size_t n_enemies, MoveFunc * f);
};

#endif
