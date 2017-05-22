#include "sdk\IClientEntityList.h"
#include "sdk\Player.h"
#include "Engine\Memory.h"


namespace ExtCSGO::sdk
{
	static int m_EntityList = 0;

	IClientEntityList::IClientEntityList() : 
		m_Entity(new Player[MaxEntityIndex]),
		m_Matrix(new s_matrix3x4[MaxEntityIndex])
	{
		m_BoneId = 8;
	}

	IClientEntityList::~IClientEntityList()
	{
		delete m_Matrix;
		delete m_Entity;
	}

	vec3 IClientEntityList::GetBonePosition(const int & EntityIndex) const
	{
		return vec3(m_Matrix[EntityIndex].Matrix[0][3], m_Matrix[EntityIndex].Matrix[1][3], m_Matrix[EntityIndex].Matrix[2][3]);
	}

	Player* IClientEntityList::GetClientEntity(const int & EntityIndex) const
	{
		return &m_Entity[EntityIndex];
	}

	void IClientEntityList::SetBoneId(const int & Id)
	{
		m_BoneId = Id;
	}

	void IClientEntityList::Update(const Process *Process, const Module* ClientDLL) const
	{
		for (int i = 0; i < MaxEntityIndex; i++)
		{
			static DWORD Ptr = 0;
			if (!Process->ReadMemory
			(
				(PVOID)((DWORD64)ClientDLL->GetdwBaseAddress() + m_EntityList + i * 0x10),
				&Ptr, sizeof(DWORD)
			))
			{
				continue;
			}

			if (!Process->ReadMemory
			(
				(PVOID)((DWORD64)Ptr),
				&m_Entity[i], sizeof(Player)
			))
			{
				continue;
			}

			if (!Process->ReadMemory
			(
				(PVOID)((DWORD64)m_Entity[i].GetdwBoneMatrix() + m_BoneId * 0x30),
				&m_Matrix[i], sizeof(s_matrix3x4)
			))
			{
				continue;
			}
		}
	}

	void InitIClientEntityOffsets(FILE*& File)
	{
		m_EntityList = std::stoi(Tools::ReadString(File, "EntityList="), NULL, NULL);
	}
}