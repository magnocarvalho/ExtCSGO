#pragma once
#include "..\Netvars.h"
#include "Tools.h"

namespace ExtCSGO
{
	class Process;
	class Module;
	class vec3;
}

namespace ExtCSGO::sdk
{
	extern int ViewAngles_Offset;
	class IVEngineClient
	{
		char 	m_IVEngine[0x10000];
	public:
		int 	GetLocalPlayer() const;
		vec3 	GetViewAngles() const;
		void 	Update(const Process* Process, const Module* EngineDLL) const;
	};
	void InitIVEngineOffsets(FILE*& File);
}