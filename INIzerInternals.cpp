#include "INIzerInternals.h"

void INIzerINIManager::Initialize()
{
	_MESSAGE("INI Path: %s", GetINIPath());
	std::fstream INIStream(GetINIPath(), std::fstream::in);

	if (INIStream.fail()) {
		CreateINI = true;			
		_MESSAGE("INI File not found; Creating one...");
	}

	INIStream.close();
	INIStream.clear();

	RegisterSetting(new INISetting(this, "INI", "Filenames", "Oblivion.ini"));
	RegisterSetting(new INISetting(this, "Plugin List", "Filenames", "Plugins.txt"));
}

INIzerINIManager*	g_INIManager = new INIzerINIManager();
std::string			PluginList_A, PluginList_B;