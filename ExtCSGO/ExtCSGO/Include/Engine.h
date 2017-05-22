#pragma once
#include <windows.h>
#include "sdk\sdk.h"

namespace ExtCSGO::Engine
{
	void                                 StartEngine(const std::string & GamePath, const std::string & LaunchOptions);
	void                                 ShutdownEngine();
	void                                 UpdateEngine();
	void                                 UpdateEvents();
	bool                                 IsValid();

	sdk::IClientEntityList*              GetIClientEnt();
	sdk::IVEngineClient*                 GetIVEngine();
}