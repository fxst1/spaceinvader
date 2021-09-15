#ifndef ENGINE_ABSTRACT_HH
# define ENGINE_ABSTRACT_HH

namespace engine {

	class		Box;
	class		Entity;
	class		Engine;

	class		Renderable {
		public:
			virtual ~Renderable(void) {}
			virtual void	render(engine::Box const & dst) = 0;
	};

	class		TickHandler {
		public:
			virtual ~TickHandler(void) {}
			virtual void	tick(engine::Engine & engine) = 0;
	};

	class		Interaction {
		public:
			virtual ~Interaction(void);

			virtual bool	canOutScene(void) = 0;
			virtual void	onOutScene(engine::Engine & engine) = 0;

			virtual bool	canCollide(engine::Entity & e) = 0;
			virtual void	onCollide(engine::Engine & engine, engine::Entity & e) = 0;

			virtual void	onDestroy(engine::Engine & engine) = 0;
	};

};

#endif
