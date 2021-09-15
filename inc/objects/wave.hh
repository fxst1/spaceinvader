#ifndef SPACEINVADER_WAVE_HH
# define SPACEINVADER_WAVE_HH
# include "spaceinvader.hh"
# include "objects/spaceship.hh"

class		MoveFunc {
	protected:
		double	_speed;

	public:
		MoveFunc(double speed = 1.0): _speed(speed) {}
		virtual ~MoveFunc(void) {}
		virtual void	operator()(engine::Entity *it, engine::Engine & e) = 0;
};

class		MoveSinusFunc: public MoveFunc {
	private:
		double	_y_max;
		double	_amplitude;

	public:
		MoveSinusFunc(void):
			MoveFunc(),
			_y_max(200),
			_amplitude(100)
		{}
		MoveSinusFunc(double speed, double y_max, double amplitude):
			MoveFunc(speed),
			_y_max(y_max),
			_amplitude(amplitude)
		{}

		virtual ~MoveSinusFunc(void) {}

		virtual void	operator()(engine::Entity *it, engine::Engine & e) {

			double		center = (e.getScene().getH() / 2) - (it->getH() / 2);
			double		tmp = (e._delta_time * _speed);
			double		x = it->getX() - ( ((int)tmp) == 0 ? 1 : tmp);
			double		v = sin(x / _amplitude);

			it->setY( center + (v * _y_max) );
			it->setX(x);
		}
};

class		MoveFunc_Wave1_2: public MoveFunc {
	private:
		int		_phase;
		double	_angle;

	public:
		MoveFunc_Wave1_2(void);
		MoveFunc_Wave1_2(double speed);
		virtual ~MoveFunc_Wave1_2(void);

		virtual void	operator()(engine::Entity *it, engine::Engine & e);
};

class	Wave: public engine::Entity {
	public:

		class		EnemyShip: public engine::Entity {
			public:
				EnemyShip(Wave *parent);
				EnemyShip(Wave *parent, MoveFunc* mvfunc);
				virtual ~EnemyShip(void);

				virtual void		onInit(engine::Engine & engine);
				virtual void		onCollide(engine::Engine & engine, engine::Entity & e);
				virtual void		tick(engine::Engine & e);
				virtual void		onDestroy(engine::Engine & e);

				virtual bool		canOutScene(void) const;
				virtual bool		canCollide(engine::Entity const & e) const;

				virtual void 		lossPv(engine::Engine & eng);
				virtual std::string	ID(void) const;
			protected:
				virtual void		moveTick(engine::Engine & e);
				void				shoot(engine::Engine & e, engine::Box const &oldpos);
				void				populateBullet(engine::Engine & e);

			private:

				Wave*		_group;
				int			_pv;
				int			_last_shoot;
				int			_recovery;
				MoveFunc*	_move_func;
		};

		Wave(std::size_t n_enemies, MoveFunc* mvfunc);
		virtual ~Wave(void);

		virtual void 		populate(engine::Engine & e, Game &g);
		void 				remove(Wave::EnemyShip *en, engine::Engine & engine);

		bool				isEmpty(void) const;

		virtual bool		canOutScene(void) const;
		virtual bool		canCollide(engine::Entity const & e) const;
		virtual void 		onOutScene(engine::Engine & e);
		virtual void		onDestroy(engine::Engine & engine);

		void				moveFunc(engine::Entity * ent, engine::Engine & eng);

	protected:

		std::size_t					_n_ennemies;
		std::list<Wave::EnemyShip*>	_enemies;
		MoveFunc*					_move_func;

};

class	Wave1_2 : public Wave {
	public:
		Wave1_2(void);
		virtual ~Wave1_2(void);

		virtual void 		populate(engine::Engine & e, Game &g);
};

#endif
