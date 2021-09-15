#ifndef ENGINE_GC_HH
# define ENGINE_GC_HH

# include "driver/ncurses/NCursesDrv.hh"
# include "engine/engine.hh"

namespace	engine {
	class	NCursesGameController: public GameController {
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
			virtual void	onPreRender(void);
			virtual void	onPostRender(void);

	};
};

#endif
