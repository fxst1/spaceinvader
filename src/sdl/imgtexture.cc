#include "driver/SDL/ImgTexture.hh"

engine::SdlTexture::SdlTexture(std::string const &filename, SDL_Renderer* r):
	engine::Texture(),
	_texture(nullptr),
	_renderer(r),
	_angle(0),
	_flip(),
	_center()
{
	_flip = (SDL_RendererFlip) static_cast<SDL_RendererFlip>(0);
	_texture = IMG_LoadTexture(this->_renderer, filename.c_str());
	SDL_QueryTexture(this->_texture, NULL, NULL, &this->_w, &this->_h);

	_center.x = this->getW() / 2;
	_center.y = this->getH() / 2;
}

engine::SdlTexture::SdlTexture(std::string const &filename, SDL_Renderer* r, double angle, SDL_RendererFlip flip):
	engine::Texture(),
	_texture(nullptr),
	_renderer(r),
	_angle(angle),
	_flip(flip),
	_center()
{
	_texture = IMG_LoadTexture(this->_renderer, filename.c_str());
	SDL_QueryTexture(this->_texture, NULL, NULL, &this->_w, &this->_h);

	_center.x = this->getW() / 2;
	_center.y = this->getH() / 2;
}
engine::SdlTexture::SdlTexture(std::string const &filename, SDL_Renderer* r, double angle, int flip):
	engine::Texture(),
	_texture(nullptr),
	_renderer(r),
	_angle(angle),
	_flip(static_cast<SDL_RendererFlip>(flip)),
	_center()
{
	_texture = IMG_LoadTexture(this->_renderer, filename.c_str());
	SDL_QueryTexture(this->_texture, NULL, NULL, &this->_w, &this->_h);

	_center.x = this->getW() / 2;
	_center.y = this->getH() / 2;
}
engine::SdlTexture::~SdlTexture(void) {
	SDL_DestroyTexture(_texture);
}

void	engine::SdlTexture::useRenderer(SDL_Renderer* renderer) {
	this->_renderer = renderer;
}

void	engine::SdlTexture::render(engine::Box const &b) {

	SDL_Rect dst;
	dst.x = b.getX();
	dst.y = b.getY();
	dst.w = this->getW();
	dst.h = this->getH();

	SDL_Rect src;
	src.x = this->getX();
	src.y = this->getY();
	src.w = this->getW();
	src.h = this->getH();

// Uncomment for debug
//	SDL_SetRenderDrawColor((SDL_Renderer*)this->_renderer, 255, 255, 255, 255);
//	SDL_RenderFillRect(this->_renderer, &dst);


	SDL_RenderCopy(this->_renderer, this->_texture, &src, &dst);

	(void)this->_angle;
	(void)this->_flip;
	(void)this->_center;
}

/***********************/

engine::SdlAnimation::SdlAnimation(bool cyclic, engine::Texture* r):
	engine::Animation(cyclic, r)
{}
engine::SdlAnimation::~SdlAnimation(void) {}
