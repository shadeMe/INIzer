#include "INIzerInternals.h"

IDebugLog					gLog("INIzer.log");

PluginHandle				g_pluginHandle = kPluginHandle_Invalid;

extern "C" {

bool OBSEPlugin_Query(const OBSEInterface * obse, PluginInfo * info)
{
	info->infoVersion = PluginInfo::kInfoVersion;
	info->name = "INIzer";
	info->version = 1;

	if(!obse->isEditor)
	{
		if(obse->obseVersion < OBSE_VERSION_INTEGER)
		{
			_ERROR("OBSE version too old (got %08X expected at least %08X)", obse->obseVersion, OBSE_VERSION_INTEGER);
			return false;
		}

		if(obse->oblivionVersion != OBLIVION_VERSION)
		{
			_ERROR("incorrect Oblivion version (got %08X need %08X)", obse->oblivionVersion, OBLIVION_VERSION);
			return false;
		}
	}
	else
	{
		return false;		// as they say, don't fuch with the editor
	}

	return true;
}

bool OBSEPlugin_Load(const OBSEInterface * obse)
{
	g_pluginHandle = obse->GetPluginHandle();

	g_INIManager->SetINIPath(std::string(obse->GetOblivionDirectory()) + "Data\\OBSE\\Plugins\\INIzer.ini");
	g_INIManager->Initialize();

	_MESSAGE("\nINI Options:\n\tINI = %s\n\tPlugin List = %s\n",
		g_INIManager->GET_INI_STRING("INI"),
		g_INIManager->GET_INI_STRING("Plugin List"));

	PluginList_A = ".\\" + std::string(g_INIManager->GET_INI_STRING("Plugin List")),
	PluginList_B = "%s" + std::string(g_INIManager->GET_INI_STRING("Plugin List"));

	SafeWrite32(kINIFileNameStringTableAddr, (UInt32)g_INIManager->GET_INI_STRING("INI"));
	SafeWrite32(kPluginListFileNameStringTableAddr, (UInt32)PluginList_A.c_str());
	SafeWrite32(kPluginListFileNameLoadArchivesAddr, (UInt32)PluginList_B.c_str());

	_MESSAGE("INIzer initialized!");
	return true;
}

};
