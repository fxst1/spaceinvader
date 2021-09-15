#ifndef ENGINE_HH
# define ENGINE_HH

# include <fstream>
# include <iostream>
# include <list>
# include <vector>
# include <map>
# include <unordered_set>
# include <functional>
# include<algorithm>
# include <chrono>
# include <thread>
# include <iostream>
# include <ratio>

# include "engine/entity.hh"

namespace	engine {

	class	GameController;

	class	Engine: public engine::Values {

		private:

			std::chrono::time_point<std::chrono::milliseconds>	_tick_time;

			std::unordered_set<engine::Entity*>		_background;
			std::unordered_set<engine::Entity*>		_objects;
			std::unordered_set<engine::Entity*>		_garbage;
			std::unordered_set<engine::Entity*>		_loaded;

			engine::Box								_scene;
			engine::Box								_camera;

			engine::GameController*					_game;

		public:

			std::ofstream					_log;
			long							_delta_time;

			Engine(void);
			~Engine(void);

			void 						init(void);
			void 						tick(void);

			double						getDeltaTime(double factor = 1) const;

			bool						overlay( engine::Entity *a, engine::Entity *b );

			void						addEntity(engine::Entity *e);
			void						addRenderEntity(engine::Entity *e);
			void						removeEntity(engine::Entity *e);

			void						setGameController(engine::GameController *game);
			engine::GameController*		getGameController(void);

			engine::Box&				getScene(void);
			engine::Box&				getCamera(void);
	};


	class	GameController {
		private:

			bool										_start;
			std::map<std::string, engine::Texture*>		_textures;

		protected:

			engine::Engine								_engine;

		public:

			GameController(void);
			virtual ~GameController(void);

			bool				isRunning(void) const;
			void				start(void);
			void				stop(void);
			void				mainloop(void);

			virtual void		loop(void) = 0;
			virtual void		tick(void) = 0;

			virtual void		onPreRender(void) = 0;
			virtual void		onPostRender(void) = 0;

			virtual void		onStart(void) = 0;
			virtual void		onStop(void) = 0;

			virtual engine::Texture*    allocTexture(std::string const &name, std::string const &path) = 0;
	};
};

#endif
