#ifndef PLATFORM_HH
# define PLATFORM_HH

# include <ncurses.h>
# include <map>
# include <random>

# include "engine/box.hh"
# include "engine/engine.hh"
# include "ascii.hh"

class	PlatformEntity: public engine::Entity {

	private:

		int		_on_out_scene;

	public:

		PlatformEntity(void);
		virtual ~PlatformEntity(void);

		void	setTexture(AsciiTexture* t);

		bool	canOutScene(void) const;
		void	onOutScene(engine::Engine & engine);
		void	onDestroy(engine::Engine & engine);
};


class	BulletEntity: public SpaceInvaderEntity {
	protected:
		SpaceInvaderEntity& _parent;
		int					_xdir;
		std::string			_collide_on;

	public:
		BulletEntity(SpaceInvaderEntity & parent, int x_dir, std::string const &collide_on);
		~BulletEntity(void);

		virtual std::string	ID(void) const;

		virtual bool		canCollide(engine::Entity const &e) const;
		virtual void		onCollide(engine::Engine & engine, engine::Entity & e);
		virtual void 		onDestroy(engine::Engine & e);

		virtual void		tick(engine::Engine & e);
};

class	SpaceShip: public SpaceInvaderEntity {

	private:

		int		_pv;

	public:
		SpaceShip();
		~SpaceShip();

		void lossPv(void);

		virtual std::string	ID(void) const;
		virtual void		tick(engine::Engine & e);


		class		Bullet : public BulletEntity {
			public:
				Bullet(SpaceShip &parent);
				~Bullet(void);

		};
};

class	EnemyShip: public SpaceInvaderEntity {
	public:
		EnemyShip(void);
		~EnemyShip();

		virtual std::string	ID(void) const;
		virtual void		tick(engine::Engine & e);
		virtual void 		onDestroy(engine::Engine & e);

		class		Bullet : public BulletEntity {
			public:
				Bullet(EnemyShip &parent);
				~Bullet(void);
		};
};

class	BackgroundTexture : public SpaceInvaderEntity {
	public:
		BackgroundTexture(AsciiTexture *texture, engine::speed_t sp);
		virtual ~BackgroundTexture(void);

		virtual void 	tick(engine::Engine & engine);
		virtual bool	canOutScene(void) const;
		virtual void	onOutScene(engine::Engine & engine);
		virtual void	onDestroy(engine::Engine & engine);

};

class	Game: public engine::GameController {
	private:

		std::size_t					_n_ennemies;
		SpaceShip					_player;
		engine::Engine				_engine;
		engine::Box					_oldscene;

		void						populateBackground(void);
		void						tick(void);

	public:

		Game(void);
		~Game(void);

		std::map<std::string, AsciiTexture*>	_textures;

		void			loop(void);
		virtual void			onPreRender(void);
		virtual void			onPostRender(void);

	protected:

		virtual void			onStart(void);
		virtual void			onStop(void);
};

class	Explosion: public BackgroundTexture {
	private:
		engine::Box		_parent;
		AsciiTexture*	_texture_1;
		AsciiTexture*	_texture_2;
		AsciiTexture*	_texture_3;

	public:
		Explosion(Game *g, engine::Box const & parent);
		~Explosion(void);

		virtual std::string	ID(void) const;

		void tick(engine::Engine & engine);
};
#endif
