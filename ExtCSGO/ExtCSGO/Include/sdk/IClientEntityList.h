#pragma once
#include <vector>
#include "..\Maths\Vector.h"
#include "Tools.h"

#define MaxEntityIndex 32

namespace ExtCSGO
{
	class Process;
	class Module;
}

namespace ExtCSGO::sdk
{
	class Player;

	struct s_matrix3x4
	{
		matrix3x4_t Matrix;
	};

	class IClientEntityList
	{
		Player*        m_Entity;
		s_matrix3x4*   m_Matrix;
		int            m_BoneId;
	public:
		IClientEntityList();
		~IClientEntityList();

		vec3 GetBonePosition(const int & EntityIndex) const;
		Player* GetClientEntity(const int & EntityIndex) const;

		void SetBoneId(const int & Id);
		void Update(const Process *Process, const Module* ClientDLL) const;
	};
	void InitIClientEntityOffsets(FILE*& File);
}