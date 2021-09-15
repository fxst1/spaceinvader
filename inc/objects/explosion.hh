#ifndef SPACEINVADER_EXPLOSION_HH
# define SPACEINVADER_EXPLOSION_HH
# include "spaceinvader.hh"

class	Explosion: public engine::Animation {

	public:

		Explosion(engine::Texture *t);
		~Explosion(void);

};

class	ExplosionEntity: public engine::Entity {

	private:

		Explosion*			_animation;

	public:

		ExplosionEntity(Game *g, engine::Box const & parent);
		~ExplosionEntity(void);

		void				tick(engine::Engine & e);
		virtual std::string	ID(void) const;

};

#endif
