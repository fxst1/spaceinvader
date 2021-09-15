#include "driver/ncurses/ascii.hh"
#include <iostream>
#include <vector>

AsciiTexture::AsciiTexture(void):
	engine::Texture(),
	_map()
{}

AsciiTexture::~AsciiTexture(void)
{
	delete[] _buf;
}


AsciiTexture*		AsciiTexture::loadFromFile(std::string const &filename) {
	std::ifstream	input(filename);
	AsciiTexture* ret = new AsciiTexture();

    std::cout << "TEXTURE: " << filename << ":" << input.is_open() << std::endl;

	if (input.is_open()) {

		char					c = 0;
		int						n_line = 0;
		int						n_col = 0;

		input >> n_col;
		input.read(&c, sizeof(char));
		input >> n_line;

		std::string					line;
		std::vector<std::string>	lines;

		//skip 1st line
		std::getline( input , line );

		while (std::getline( input , line )) {
			lines.push_back( line );
		}
		input.close();

		AsciiTexture::pix_t*	pixels = new AsciiTexture::pix_t[n_line * (n_col + 1)];
		AsciiTexture::pix_t*	buf = pixels;

		/*************
		**	draw
		**************/

		for (std::size_t i = 0; i < (std::size_t)n_line; i++) {

			std::size_t	j = 0;
			while (j < lines[i].size() && j < (std::size_t)n_col) {
				buf->value = lines[i][j];
				buf++;
				j++;
			}

			while (j < (std::size_t)n_col) {
				buf->value = 0;
				buf++;
				j++;
			}

			buf->value = '\n';
			buf++;
		}


		/*************
		**	color fg
		**************/
		buf = pixels;
		for (std::size_t i = n_line; i < (std::size_t)(n_line * 2); i++) {

			std::size_t	j = 0;
			while (j < lines[i].size() && j < (std::size_t)n_col) {
				buf->fgcolor = lines[i][j];
				buf++;
				j++;
			}

			while (j < (std::size_t)n_col) {
				buf->fgcolor = 0;
				buf++;
				j++;
			}

			buf->fgcolor = 0;
			buf++;
		}

		ret = new AsciiTexture();
		ret->_buf = pixels;
		ret->_bufsize = n_line * n_col;
		ret->_w = n_col;
		ret->_h = n_line;

	} else {
		std::cerr << "ERROR" << std::endl;
	}
	return (ret);
}

void		AsciiTexture::setMap(AsciiTexture::ColorMap &map) {
	this->_map = map;
}


void		AsciiTexture::render(engine::Box const &src) {
	AsciiTexture::pix_t		*p = this->_buf;

	for (std::size_t y = 0; y < (std::size_t)this->_h; y++) {
		for (std::size_t x = 0; x < (std::size_t)this->_w; x++) {
			if (p->value != 0 && p->value != '\n') {
				attron(COLOR_PAIR(p->fgcolor));
				mvaddch((int)y + src.getY(), (int)x + src.getX(), (int)p->value);
				attron(COLOR_PAIR(p->fgcolor));
			}
			p++;
		}
		p++;
	}
}

/*************************************/


CompositeAsciiTexture::CompositeAsciiTexture(int w, int h):
	engine::Texture(),
	_textures(),
	_width(w),
	_height(h)
{}

CompositeAsciiTexture::~CompositeAsciiTexture(void)
{}

void				CompositeAsciiTexture::useTexture(AsciiTexture * texture) {
	this->_textures.push_back(texture);
}

void				CompositeAsciiTexture::render(engine::Box const &src) const {
	(void)src;
	(void)_width;
	(void)_height;
}

