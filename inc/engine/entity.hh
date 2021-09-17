#ifndef ENGINE_ENTITY_HH
# define ENGINE_ENTITY_HH

# include <list>
# include <string>

# include "engine/types.hh"
# include "engine/box.hh"

namespace engine {

	class		Engine;

	class		Entity: public engine::Box, public engine::Values {
		private:

			engine::Texture*		_texture;
			engine::Box			_viewport;

		public:

			Entity(void);
			~Entity(void);

			virtual std::string		ID(void) const;

			virtual bool			canCollide(engine::Entity const & e) const;
			virtual void			onCollide(engine::Engine & engine, engine::Entity & e);

			virtual bool			canOutScene(void) const;
			virtual void			onOutScene(engine::Engine & engine);
			virtual void			onDestroy(engine::Engine & engine);

			virtual void			tick(engine::Engine & engine);

			void					setTexture(engine::Texture* t);
			engine::Texture*		getTexture(void);
			engine::Box&			getViewport(void);
	};

};

#endif
