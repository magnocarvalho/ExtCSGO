#pragma once

namespace ExtCSGO::sdk
{
	class IClientEntityList;
	class IVEngineClient;
	class Player;
}

namespace ExtCSGO::Features
{
	void Aimbot (
		const sdk::IClientEntityList* IClientEntity,
		const sdk::IVEngineClient*    IVEngine,
		const int&                    AimKey,
		const float&                  AimFov,
		const int&                    AimSmooth,
		const float&                  Sensitivity);

	void Triggerbot (
		const sdk::IClientEntityList* IClientEntity,
		const sdk::IVEngineClient*    IVEngine,
		const int&                    TriggerKey,
		const int&                    TriggerBurst);
}