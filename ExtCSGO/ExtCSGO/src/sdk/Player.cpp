#include "sdk\Player.h"
#include "Maths\Vector.h"

namespace ExtCSGO::sdk
{
	static int m_iHealth = 0;
	static int m_iTeamNum = 0;
	static int m_LifeState = 0;
	static int m_iShotsFired = 0;
	static int m_CrosshairId = 0;
	static int m_VecOrigin = 0;
	static int m_VecView = 0;
	static int m_aimPunchAngle = 0;
	static int m_BoneMatrix = 0;
	static int m_Dormant = 0;

	int Player::GetHealth() const 
	{
		static int result = -1;
		Tools::GetArrayData(m_Player, m_iHealth, &result);
		return result;
	}

	int Player::GetTeamNum() const
	{
		static int result = -1;
		Tools::GetArrayData(m_Player, m_iTeamNum, &result);
		return result;
	}

	int Player::GetLifeState() const
	{
		static int result = -1;
		Tools::GetArrayData(m_Player, m_LifeState, &result);
		return result;
	}

	int Player::GetShotsFired() const
	{
		static int result = -1;
		Tools::GetArrayData(m_Player, m_iShotsFired, &result);
		return result;
	}

	int Player::GetCrosshairId() const
	{
		static int result = -1;
		Tools::GetArrayData(m_Player, m_CrosshairId, &result);
		return result;
	}

	vec3 Player::GetOrigin() const
	{
		static vec3 result;
		Tools::GetArrayData(m_Player, m_VecOrigin, &result);
		return result;
	}

	vec3 Player::GetVecView() const
	{
		static float result[2];
		Tools::GetArrayData(m_Player, m_VecView + 0x4, &result);
		return vec3(0.f, result[0], result[1]);
	}

	vec3 Player::GetEyePosition() const
	{
		return vec3(GetOrigin() + GetVecView());
	}

	vec3 Player::GetVecPunch() const
	{
		static vec3 result;
		Tools::GetArrayData(m_Player, m_aimPunchAngle, &result);
		return result;
	}

	uint32_t Player::GetdwBoneMatrix() const
	{
		static uint32_t result = 0;
		Tools::GetArrayData(m_Player, m_BoneMatrix, &result);
		return result;
	}

	bool Player::IsDormant() const
	{
		static bool result = false;
		Tools::GetArrayData(m_Player, m_Dormant, &result);
		return result;
	}

	bool Player::IsValid() const
	{
		if (this->GetHealth() < 1 && this->GetHealth() > 1337)
			return false;

		if (this->IsDormant())
			return false;

		if (this->GetLifeState() != 0)
			return false;

		return true;
	}

	void InitPlayerOffsets(FILE*& File)
	{
		m_iHealth = std::stoi(Tools::ReadString(File, "m_iHealth="), NULL, NULL);
		m_iTeamNum = std::stoi(Tools::ReadString(File, "m_iTeamNum="), NULL, NULL);
		m_LifeState = std::stoi(Tools::ReadString(File, "m_LifeState="), NULL, NULL);
		m_iShotsFired = std::stoi(Tools::ReadString(File, "m_iShotsFired="), NULL, NULL);
		m_CrosshairId = std::stoi(Tools::ReadString(File, "m_iCrosshairId="), NULL, NULL);
		m_VecOrigin = std::stoi(Tools::ReadString(File, "m_vecOrigin="), NULL, NULL);
		m_VecView = std::stoi(Tools::ReadString(File, "m_vecViewOffset="), NULL, NULL);
		m_aimPunchAngle = std::stoi(Tools::ReadString(File, "m_aimPunchAngle="), NULL, NULL);
		m_BoneMatrix = std::stoi(Tools::ReadString(File, "m_dwBoneMatrix="), NULL, NULL);
		m_Dormant = std::stoi(Tools::ReadString(File, "m_Dormant="), NULL, NULL);
	}
}