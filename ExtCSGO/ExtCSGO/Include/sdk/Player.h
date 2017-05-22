#pragma once
#include <iostream>
#include "Tools.h"

namespace ExtCSGO
{
	class vec3;
}

namespace ExtCSGO::sdk
{	
	class Player
	{
		char	 m_Player[0x10000];
	public:
		int 	 GetHealth() const;
		int 	 GetTeamNum() const;
		int 	 GetLifeState() const;
		int 	 GetShotsFired() const;
		int 	 GetCrosshairId() const;

		vec3 	 GetOrigin() const;
		vec3 	 GetVecView() const;
		vec3 	 GetEyePosition() const;
		vec3 	 GetVecPunch() const;
		uint32_t GetdwBoneMatrix() const;

		bool 	 IsDormant() const;
		bool 	 IsValid() const;
	};
	void InitPlayerOffsets(FILE*& File);
}