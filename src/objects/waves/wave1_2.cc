#include "gameobjects.hh"

MoveFunc_Wave1_2::MoveFunc_Wave1_2(void):
	MoveFunc(),
	_phase(0),
	_angle(1.57075)
{}
MoveFunc_Wave1_2::MoveFunc_Wave1_2(double speed):
	MoveFunc(speed),
	_phase(0),
	_angle(1.57075)
{}

MoveFunc_Wave1_2::~MoveFunc_Wave1_2(void) {}

void	MoveFunc_Wave1_2::operator()(engine::Entity *it, engine::Engine & e) {

	double	y_c = (e.getScene().getH() / 2) - (it->getH() / 2);
	double	x_c = (e.getScene().getW() / 2) - (it->getW() / 2);

	if (_phase == 0) {
		it->setY( y_c );
		it->moveRel(-e._delta_time * 0.5, 0);

		if (x_c + 200 >= it->getX())
			_phase = 1;
	}

	if (_phase == 1) {

//		std::cout << "1>" << _angle << " = " << (x_c + (400 * sin(_angle))) << ", " << y_c + (400 * cos(_angle)) << std::endl;

		it->move(
			x_c + (200 * sin(_angle)),
			y_c + (200 * cos(_angle))
		);

		_angle += e._delta_time * (3.1415 / 8000);
		if (_angle >= (3.1415 / 2) * 5) {
			_phase = 2;
		}

	}

	if (_phase == 2) {
		it->setY( y_c );
		it->moveRel(e._delta_time * 0.5, 0);
	}

}


Wave1_2::Wave1_2(void):
	Wave(10, nullptr) {
}
Wave1_2::~Wave1_2(void) {
	delete _move_func;
}

void 		Wave1_2::populate(engine::Engine & e, Game &g) {

	Wave::EnemyShip*	prev_en = nullptr;
	for (std::size_t i = 0; i < _n_ennemies; i++) {

		Wave::EnemyShip*	en = new Wave::EnemyShip(this, new MoveFunc_Wave1_2());
		en->setTexture( g.getTexture("spider") );
		en->resize(
			en->getTexture()->getW(),
			en->getTexture()->getH()
		);
		en->setZ(1);

		if (prev_en == nullptr) {
			en->move(
				(int)e.getScene().getW() + 400,
				(int)(e.getScene().getH() / 2) - (en->getH() / 2)
			);
		}
		else {
			en->move(prev_en->getX() + 400, prev_en->getY());
		}

		prev_en = en;
		this->_enemies.push_back(en);
		e.addEntity(en);
	}

}
