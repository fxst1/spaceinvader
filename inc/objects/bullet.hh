#ifndef SPACEINVADER_BULLET_HH
# define SPACEINVADER_BULLET_HH
# include "spaceinvader.hh"

class	Bullet: public engine::Entity {
	protected:
		double				_xdir;
		double				_ydir;
		std::string			_collide_on;
		std::string			_parent_id;

	public:

		Bullet(engine::Entity const & parent, std::string const &collide_on, double x_dir, double y_dir);
		virtual ~Bullet(void);

		virtual std::string	ID(void) const;

		virtual void 		onDestroy(engine::Engine & e);
		virtual void		tick(engine::Engine & e);
};

class	EnemyBullet: public Bullet {
	public:
		EnemyBullet(engine::Entity const & parent, double x_dir, double y_dir);
};

class	PlayerBullet: public Bullet {
	public:
		PlayerBullet(engine::Entity const & parent, double x_dir, double y_dir);
};


#endif
