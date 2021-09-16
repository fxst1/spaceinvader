#ifndef ENGINE_ASCIITEXTURE_HH
# define ENGINE_ASCIITEXTURE_HH
#  include <ncurses.h>
#  include "engine/box.hh"
#  include <string>
#  include <cstring>
#  include <cstdlib>
#  include <fstream>
#  include <iostream>
#  include <map>
#  include <list>

class	AsciiTexture: public engine::Texture {

	public:

		typedef struct {
			int			value;
			int			fgcolor;
			int			bgcolor;
		}	pix_t;

		class ColorMap {
			private:
				std::map< std::pair<int,int>, int>			_map;

			public:
				ColorMap(void):
					_map()
				{}

				void	set(int c, int fg, int bg) {
					std::pair<int, int>	p = std::make_pair<>(fg, bg);
					init_pair(c, fg, bg);
					this->_map[p] = c;
				}
				int		get(int fg, int bg) const {
					std::pair<int, int>	p = std::make_pair<>(fg, bg);
					auto it = this->_map.find(p);
					return (it->second);
				}
		};

		AsciiTexture(void);
		~AsciiTexture(void);

		static AsciiTexture*	loadFromFile(std::string const &filename);
		void 		render(engine::Box const &src) ;

		void		setMap(AsciiTexture::ColorMap &map);

	protected:

		AsciiTexture::pix_t*		_buf;
		std::size_t					_bufsize;
		AsciiTexture::ColorMap		_map;

};

class	CompositeAsciiTexture : public engine::Texture {
	public:
		CompositeAsciiTexture(int w, int h);
		~CompositeAsciiTexture(void);

		void			useTexture(AsciiTexture * texture);
		void			render(engine::Box const & b);

	private:
		std::list<AsciiTexture*>	_textures;
		int							_width;
		int							_height;
};

#endif
