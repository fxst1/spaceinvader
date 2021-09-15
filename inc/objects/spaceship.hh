#ifndef SPACEINVADER_SPACESHIP_HH
# define SPACEINVADER_SPACESHIP_HH
# include "objects/wave.hh"
# include "spaceinvader.hh"
# include "objects/factory.hh"

class	SpaceShip: public engine::Entity {

	private:

		int		_pv;
		int		_last_shoot;
		int		_energy;
		int		_shield_recovery;
		bool	_use_shield;

		class	Texture : public engine::Texture {
			public:
				Texture(engine::Texture *normal, engine::Texture *shield);

				void	useShield(bool on);
				void	render(engine::Box const & dst);

			private:
				engine::Texture*	_normal;
				engine::Texture*	_shield;
				bool				_use_shield;
		};
		Texture*	_player_texture;

	public:

		SpaceShip(engine::Texture* a, engine::Texture* b);
		~SpaceShip(void);

		virtual bool		canOutScene(void) const;
		virtual void 		onOutScene(engine::Engine & e);

		virtual bool		canCollide(engine::Entity const & e) const;
		virtual void		onCollide(engine::Engine & en, engine::Entity & e);
		virtual std::string	ID(void) const;

		virtual void		tick(engine::Engine & e);
		virtual void 		onDestroy(engine::Engine & e);

	protected:
		void				lossPv(engine::Engine & e);



};

#endif
