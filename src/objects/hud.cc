#include "spaceinvader.hh"

Hud::Hud(Game *g):
	_weapon_textures(),
	_max_pv(5),
	_pv(5),
	_max_shield(100),
	_shield(100)
{
	_bar_pv_container = g->getTexture("pv_bar");
	_bar_pv_fill = g->getTexture("pv_bar_color");
	_bar_shield_container = g->getTexture("shield_bar");
	_bar_shield_fill = g->getTexture("shield_bar_color");
	_score_text = g->getTexture("score_text");
	_weapon_textures["weapon-bullet"] = g->getTexture("bullet");
}
Hud::~Hud(void) {}

void 		Hud::updatePv(int pv) {
	_pv = pv;
}
void 		Hud::updateShield(int shield) {
	_shield = shield;
}
void		Hud::render(void) {

	engine::Box		dst;
	dst.setX(0);
	dst.setY(0);
	dst.setW(_bar_pv_container->getW());
	dst.setH(_bar_pv_container->getH());

	_bar_pv_container->render(dst);

	dst.setX(5);
	dst.setY(2);
	dst.setW(_bar_pv_fill->getW());
	dst.setH(_bar_pv_fill->getH());

	// _bar_pv_container->getW() _max_pv
	// _bar_pv_fill->getW()   1
	// ??? _pv

	double w_pv = ((double)(_bar_pv_container->getW() - 5)/ _max_pv);
	double w_end = w_pv * _pv;

	while (dst.getX() < w_end) {
		_bar_pv_fill->render(dst);
		dst.moveRel(
			_bar_pv_fill->getW(), 0
		);
	}

	dst.setX(0);
	dst.setY(_bar_pv_container->getH());
	dst.setW(_bar_shield_container->getW());
	dst.setH(_bar_shield_container->getH());

	_bar_shield_container->render(dst);

	dst.setX(5);
	dst.setY(dst.getY() + 2);
	dst.setW(_bar_shield_fill->getW());
	dst.setH(_bar_shield_fill->getH());

	double w_shield = ((double)(_bar_shield_container->getW() - 5)/ _max_shield);
	w_end = w_shield * _shield;

	while (dst.getX() < w_end) {
		_bar_shield_fill->render(dst);
		dst.moveRel(
			_bar_shield_fill->getW(), 0
		);
	}
}
