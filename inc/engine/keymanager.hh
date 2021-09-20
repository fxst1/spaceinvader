#ifndef ENGINE_KEYMANAGER_HH
# define ENGINE_KEYMANAGER_HH

# include <string>
# include <map>
# include <queue>
# include <utility>

namespace engine {

	class	KeyManager {
	
		public:

			class KeyEvent {
				public:
					KeyEvent(void);
					KeyEvent(std::string const &name, int value, int code);
					KeyEvent(engine::KeyManager::KeyEvent const &src);
					~KeyEvent(void);

					engine::KeyManager::KeyEvent&	operator=(engine::KeyManager::KeyEvent const &e);

					std::string const&		getName(void) const;

				protected:
					std::string	_name;
					int		_value;
					int		_code;

			};


			KeyManager(void);
	//		KeyManager(KeyManager const &src);
			~KeyManager(void);
			
			void		mapkey(std::string const &name, int driver_value);

			virtual std::string	getEventName(int v) const = 0;
			virtual void		pushEvent(void) = 0;
			virtual bool		poll(void);
			virtual void		onKey(engine::KeyManager::KeyEvent const & e) = 0;

		protected:

			std::map<std::string, std::string>			_keymanager;
			std::queue<engine::KeyManager::KeyEvent>		_event_poll;
	};

}

#endif
