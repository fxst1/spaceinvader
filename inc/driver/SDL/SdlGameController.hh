#ifndef ENGINE_GC_HH
# define ENGINE_GC_HH

# include <SDL2/SDL.h>

# include "engine/engine.hh"

namespace	engine {
	class	SdlGameController: public GameController {
		private:
			int				_width;
			int				_height;
			int				_fps;

		public:

			SdlGameController(int width, int height, int fps = 60);
			~SdlGameController(void);

			int				getWidth(void) const;
			int				getHeight(void) const;

		protected:
			SDL_Renderer*	_renderer;
			SDL_Window*		_window;

			void 			loop(void);
			virtual void	onPreRender(void);
			virtual void	onPostRender(void);
            virtual engine::Texture     *allocTexture(std::string const &name, std::string const &path);

	};
};

#endif
