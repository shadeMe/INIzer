#pragma once

#include "obse/PluginAPI.h"
#include "obse_common/SafeWrite.h"
#include "[ Libraries ]/INI Mananger/INIManager.h"


using namespace SME;
using namespace INI;

class INIzerINIManager : public INIManager
{
public:
	void					Initialize();
};

#if OBLIVION_VERSION == OBLIVION_VERSION_1_2_416
	const UInt32 kINIFileNameStringTableAddr = 0x00B02C84;
	const UInt32 kPluginListFileNameStringTableAddr = 0x00B02C88;
	const UInt32 kPluginListFileNameLoadArchivesAddr = 0x0042F75B;
#else
	#error unsupported oblivion version
#endif

extern INIzerINIManager*	g_INIManager;
extern std::string			PluginList_A, PluginList_B;
