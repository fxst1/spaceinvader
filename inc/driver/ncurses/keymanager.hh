#ifndef ENGINE_NCURSES_KEYMANAGER_HH
# define ENGINE_NCURSES_KEYMANAGER_HH

# include "engine/keymanager.hh"
# include <string>
# include <map>
# include <algorithm>
# include <sstream>

# include <ncurses.h>

namespace engine {

	class	NCursesKeyManager: public engine::KeyManager {
	
		public:

			NCursesKeyManager(void);
			
			virtual std::string	getEventName(int v) const;	
			virtual void		pushEvent(void);

		private:

			std::map<std::string, int>			_dict;
	};

}

#endif
