#include "driver/ncurses/NCursesGameController.hh"
#include <ctime>
#include <unistd.h>

engine::NCursesGameController::NCursesGameController(int width, int height, int fps):
	engine::GameController(),
	engine::NCursesKeyManager(),
	_width(width),
	_height(height),
	_fps(fps)
{
	getmaxyx(stdscr, height, width);

    _window = stdscr;//newwin(height, width, 0, 0);
    //box(_window, 0, 0);
    erase();

	//getmaxyx(stdscr, height, width);

	this->_engine.getScene().move(0, 0);
	this->_engine.getCamera().move(0, 0);

	this->_engine.getScene().resize(width + 1, height + 1);
	this->_engine.getCamera().resize(width, height);

	this->_engine.setViewport(this->_engine.getCamera());

}

engine::NCursesGameController::~NCursesGameController(void){}

engine::KeyManager&	engine::NCursesGameController::getKeyManager(void) {
	return (*this);
}

std::string         engine::NCursesGameController::getTexturePath() const {
    return ("textures/ascii/");
}

engine::Texture*    engine::NCursesGameController::allocTexture(std::string const & name, std::string const & path) {
    this->_textures[name] = AsciiTexture::loadFromFile(this->getTexturePath() + path + ".ascii");
    return (this->_textures[name]);
}

void	engine::NCursesGameController::loop(void) {

//	struct timespec sleep_time;

	std::time_t	minimum_fps_delta_time = 1000 / this->_fps;
	std::time_t	last_game_step = std::time(0); //SDL_GetTicks();

	while (this->isRunning()) {

		//_engine._delta_time = 1;
        	this->tick();

		std::time_t	now = std::time(0); //struct timespec now;
		if (last_game_step <= now) {
			std::time_t delta_time = now - last_game_step;
			if (delta_time > minimum_fps_delta_time)
				delta_time = minimum_fps_delta_time;

			_engine._delta_time = delta_time < 1 ? 1 : delta_time;

			int c = getch();
			if (c == '\n') {
				this->stop();
				break;
			}

			this->tick();

			last_game_step = now;
		} else {
			usleep(1);
		}
	}
}

int			engine::NCursesGameController::getWidth(void) const {
	return (_width);
}
int			engine::NCursesGameController::getHeight(void) const {
	return (_height);
}

void		engine::NCursesGameController::onPreRender(void) {
	erase();
}
void		engine::NCursesGameController::onPostRender(void) {
	refresh();
}
