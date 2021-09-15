class	TextSheet {

	private:

		int	_start_x;
		int	_start_y;

		int	_offset_x;
		int	_offset_y;

		engine::Box _inner;

		int	_line_size;

		SDL_Renderer*	_renderer;
		SDL_Texture*	_texture;

		static const char[]	_char_list = "abcdefghijklmnopqrstuvwxyz0123456789";

	public:

		TextSheet(SDL_Renderer * renderer, std::string const & filename, int sx, int sy, int ox, int oy, engine::Box const &inner, int n_per_line):
			_start_x(sx),
			_start_y(sx),
			_offset_x(sx),
			_offset_y(sx),
			_inner(inner),
			_line_size(n_per_line),
			_renderer(renderer)
		{
			_texture = IMG_LoadTexture(_renderer, filename.c_str());
		}
		~TextSheet(void);

		bool				load(std::string const & filename) {

		}
		engine::Texture*	text(char c) {
			return (_map[c]);
		}
};
