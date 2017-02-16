#include <string>

namespace Log{	
	void info(std::string msg, bool breakline=false);
	void err(std::string msg);
	void MouseTile();
	void MouseCord();
	void ScreenSize();
};