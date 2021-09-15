#include "engine/engine.hh"
#include "engine/box.hh"

engine::Box::Box(void):
_x(0),_y(0),_z(0),_w(0),_h(0) {}

engine::Box::Box(int x, int y):
_x(x),_y(y),_z(0),_w(0),_h(0) {}

engine::Box::Box(int x, int y, int z):
_x(x),_y(y),_z(z),_w(0),_h(0) {}

engine::Box::Box(int x, int y, int w, int h):
_x(x),_y(y),_z(0),_w(w),_h(h) {}

engine::Box::Box(int x, int y, int z, int w, int h):
_x(x),_y(y),_z(z),_w(w),_h(h) {}


engine::Box::Box(engine::Box const &src):
_x(src._x),_y(src._y),_z(src._z),_w(src._w),_h(src._h) {}
engine::Box::~Box(void) {}

engine::Box&	engine::Box::operator=(engine::Box const &box) {
	if (this != &box) {
		this->_x = box._x;
		this->_y = box._y;
		this->_z = box._z;
		this->_w = box._w;
		this->_h = box._h;
	}
	return (*this);
}

void	engine::Box::center(engine::Box const &center_from) {
	this->move(
		center_from.getX() + (center_from.getW() / 2) - (this->getW() / 2),
		center_from.getY() + (center_from.getH() / 2) - (this->getH() / 2)
	);
}
void	engine::Box::centerX(engine::Box const &center_from) {
	this->setX(
		center_from.getX() + (center_from.getW() / 2) - (this->getW() / 2)
	);
}
void	engine::Box::centerY(engine::Box const &center_from) {
	this->setY(
		center_from.getY() + (center_from.getH() / 2) - (this->getH() / 2)
	);
}

void 	engine::Box::move(int x, int y) {
	this->_x = x;
	this->_y = y;
}

void 	engine::Box::moveRel(int x, int y) {
	this->_x += x;
	this->_y += y;
}

void 	engine::Box::move(int x, int y, int z) {
	this->_x = x;
	this->_y = y;
	this->_z = z;
}

void 	engine::Box::moveRel(int x, int y, int z) {
	this->_x += x;
	this->_y += y;
	this->_z += z;
}

void 	engine::Box::resize(int w, int h) {
	this->_w = w;
	this->_h = h;
}

void 	engine::Box::setX(int x) {
	this->_x = x;
}

void 	engine::Box::setY(int y) {
	this->_y = y;
}

void 	engine::Box::setZ(int z) {
	this->_z = z;
}

void 	engine::Box::setW(int w) {
	this->_w = w;
}

void 	engine::Box::setH(int h) {
	this->_h = h;
}

int			engine::Box::getX(void) const {
	return (this->_x);
}
int			engine::Box::getY(void) const {
	return (this->_y);
}
int			engine::Box::getZ(void) const {
	return (this->_z);
}
int			engine::Box::getW(void) const {
	return (this->_w);
}
int			engine::Box::getH(void) const {
	return (this->_h);
}


bool		engine::Box::in(engine::Box const &b) const {
	return (
		this->_x <= b._x
		&& b._x + b._w <= this->_x + this->_w
		&& this->_y <= b._y
		&& b._y + b._h <= this->_y + this->_h
	);
}

bool		engine::Box::over(engine::Box const &dst) const {
	if((dst._x >= this->_x + this->_w)      // trop à droite
		|| (dst._x + dst._w <= this->_x) // trop à gauche
		|| (dst._y >= this->_y + this->_h) // trop en bas
		|| (dst._y + dst._h <= this->_y))  // trop en haut
		return false;
	else
		return true;
}

/*
bool		engine::Box::over(engine::Box const &b) const {

	for (int i = this->_x; i < this->_x + this->_w; i++) {
		for (int j = this->_y; j < this->_y + this->_h; j++) {

			if (b._x <= i && i <= b._x + b._w
				&& b._y <= j && j <= b._y + b._h) {
				return (true);
			}

		}
	}
	return (false);
}
*/

std::ostream&	operator<<(std::ostream& os, const engine::Box &b) {
	os << "Box: (x = " << std::dec << b.getX()
			<< ", y = " << std::dec << b.getY()
			<< ") -> (w = " << std::dec << b.getW()
			<< ", h = " << std::dec << b.getH()
			<< ")";
	return (os);
}

/**********************/

engine::Texture::Texture(void):
	engine::Box()
{}
engine::Texture::~Texture(void)
{}

/**********************/

engine::Animation::Animation(bool cyclic, engine::Texture *texture):
	_start(false),
	_timer(0),
	_maxtimer(0),
	_sprites(),
	_cyclic(cyclic),
	_texture(texture)
{}
engine::Animation::~Animation(void) {}

void	engine::Animation::start(void) {
	this->_start = true;
	this->_timer = 0;
}
void	engine::Animation::stop(void) {
	this->_start = false;
}
bool	engine::Animation::isStop(void) const {
	return this->_start == false;
}

void 	engine::Animation::addTexture(int duration, engine::Box const &position) {

	engine::Animation::Sprite*	s = new engine::Animation::Sprite();
	s->_duration = duration;
	s->_position = position;
	this->_sprites.push_back(s);

	this->_maxtimer += duration;
}

void	engine::Animation::render(engine::Box const &b) {

	std::uint32_t				sum = 0;
	engine::Animation::Sprite*	to_render = nullptr;

	if (this->_texture == nullptr || this->_start == false) {
		return ;
	}

	for (engine::Animation::Sprite * s: _sprites) {

		to_render = s;
		sum += s->_duration;

		if (sum >= this->_timer) {
			break;
		}
	}

	if (to_render != nullptr) {
		this->_texture->move(to_render->_position.getX(), to_render->_position.getY());
		this->_texture->resize(to_render->_position.getW(), to_render->_position.getH());
		this->_texture->render(b);
	}
}

void	engine::Animation::tick(engine::Engine & engine) {
	if (this->_start == true) {
		this->_timer += engine._delta_time;

		if (this->_timer >= this->_maxtimer) {
			if (this->_cyclic == true) {
				this->_timer %= this->_maxtimer;
			} else {
				this->_start = false;
			}
		}
	}
}
