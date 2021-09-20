#ifndef ENGINE_GC_HH
# define ENGINE_GC_HH

# include <ncurses.h>
# include "engine/engine.hh"
# include "driver/ncurses/ascii.hh"
# include "driver/ncurses/keymanager.hh"

namespace	engine {
	class	NCursesGameController: public GameController, public engine::NCursesKeyManager {
		private:
			int				_width;
			int				_height;
			int				_fps;

		public:

			NCursesGameController(int width, int height, int fps = 60);
			~NCursesGameController(void);

			int				getWidth(void) const;
			int				getHeight(void) const;

		protected:
		    WINDOW*         _window;

			void 			loop(void);
			virtual void		onPreRender(void);
			virtual void		onPostRender(void);

			engine::KeyManager&	getKeyManager(void);

            		virtual engine::Texture     *allocTexture(std::string const &name, std::string const &path);
            		virtual std::string         getTexturePath(void) const;
	};
};

#endif
