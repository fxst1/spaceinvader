#ifndef ENGINE_TYPES_HH
# define ENGINE_TYPES_HH

namespace	engine {

	typedef std::uint64_t	timer_t;
	typedef float			speed_t;

	class	Values {
		private:
			engine::speed_t			_speed;
			engine::timer_t			_timer;
			engine::timer_t			_maxtimer;

		public:
			Values(void);
			Values(engine::speed_t speed, engine::timer_t maxframe);
			~Values(void);

			void 					setSpeed(engine::speed_t speed);
			engine::speed_t			getSpeed(void) const;

			void 					setTimer(engine::timer_t timer);
			engine::timer_t			getTimer(void) const;

			void 					setMaxTimer(engine::timer_t maxtimer);
			engine::timer_t			getMaxTimer(void) const;

			void					tick(long delta_time);
	};
};

#endif
