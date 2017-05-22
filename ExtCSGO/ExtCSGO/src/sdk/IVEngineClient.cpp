#include "sdk\IVEngineClient.h"
#include "Engine\Memory.h"
#include "Maths\vector.h"

namespace ExtCSGO::sdk
{
	static int m_ClientState = 0;
	static int m_GetLocalPlayer = 0;
	static int m_ViewAngles = 0;
	int IVEngineClient::GetLocalPlayer() const
	{
		static int Angles;
		Tools::GetArrayData(m_IVEngine, m_GetLocalPlayer, &Angles);
		return Angles;
	}

	vec3 IVEngineClient::GetViewAngles() const
	{
		static vec3 Angles;
		Tools::GetArrayData(m_IVEngine, m_ViewAngles, &Angles);
		return Angles;
	}

	void IVEngineClient::Update(const Process* Process, const Module* EngineDLL) const
	{
		static DWORD Ptr = 0;
		if (!Process->ReadMemory
		(
			(PVOID)((DWORD64)EngineDLL->GetdwBaseAddress() + m_ClientState),
			&Ptr, sizeof(vec3)
		))
		{
			return;
		}

		if (!Process->ReadMemory
		(
			(PVOID)(DWORD64)(Ptr),
			(LPVOID)this, sizeof(IVEngineClient)
		))
		{
			return;
		}
	}

	void InitIVEngineOffsets(FILE*& File)
	{
		m_ClientState = std::stoi(Tools::ReadString(File, "ClientState="), NULL, NULL);
		m_GetLocalPlayer = std::stoi(Tools::ReadString(File, "GetLocalPlayer="), NULL, NULL);
		m_ViewAngles = std::stoi(Tools::ReadString(File, "GetViewAngles="), NULL, NULL);
	}
}
