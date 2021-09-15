#ifndef ENGINE_BOX_HH
# define ENGINE_BOX_HH

# include "engine/abstract.hh"

# include <iostream>
# include <fstream>

# include <list>

namespace engine {

	class	Box {
		protected:
			int		_x;
			int		_y;
			int		_z;

			int		_w;
			int		_h;

		public:
			Box(void);
			Box(int x, int y);
			Box(int x, int y, int z);
			Box(int x, int y, int w, int h);
			Box(int x, int y, int z, int w, int h);
			Box(engine::Box const &box);
			virtual ~Box(void);

			engine::Box&	operator=(engine::Box const &box);

			bool		in(engine::Box const &b) const;
			bool		over(engine::Box const &b) const;

			void		move(int x, int y);
			void		moveRel(int x, int y);
			void		move(int x, int y, int z);
			void		moveRel(int x, int y, int z);

			void 		center(engine::Box const &center_from);
			void 		centerX(engine::Box const &center_from);
			void 		centerY(engine::Box const &center_from);

			void		resize(int w, int h);

			void		setX(int x);
			void		setY(int y);
			void		setZ(int z);

			void		setW(int w);
			void		setH(int h);

			int			getX(void) const;
			int			getY(void) const;
			int			getZ(void) const;

			int			getW(void) const;
			int			getH(void) const;
	};

	class	Texture : public engine::Box, public engine::Renderable {
		public:
			Texture(void);
			virtual ~Texture(void);

			virtual void 	render(engine::Box const &src) = 0;
	};

	class	Animation: public engine::Texture {
		public:

			struct	Sprite {
				std::uint32_t				_duration;
				engine::Box					_position;
			};

			Animation(bool cyclic, engine::Texture *texture);
			~Animation(void);

			void			start(void);
			void			stop(void);
			bool			isStop(void) const;

			virtual void	tick(engine::Engine & engine);
			virtual void 	render(engine::Box const &src);

			void 			addTexture(int duration, engine::Box const &position);

		private:
			bool											_start;
			std::uint32_t									_timer;
			std::uint32_t									_maxtimer;
			std::list<engine::Animation::Sprite*>			_sprites;
			std::list<engine::Animation::Sprite*>::iterator	_current;
			bool											_cyclic;

		protected:
			engine::Texture*								_texture;
	};

}

std::ostream&	operator<<(std::ostream& os, const engine::Box &b);


#endif
