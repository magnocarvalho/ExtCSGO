#include "Features\Features.h"
#include <windows.h>

#include "sdk\sdk.h"

namespace ExtCSGO::Features
{
	using namespace sdk;

	enum ButtonState : bool
	{
		Button_Press = true,
		Button_Release = false
	};

	static bool GetTarget (
		const IClientEntityList* IClientEntity,
		const IVEngineClient*    IVEngine );

	static void ClickLeftButton(const bool & Flags, const int & ClickBurst);

	void Triggerbot (
		const IClientEntityList* IClientEntity,
		const IVEngineClient*    IVEngine,
		const int&               TriggerKey,
		const int&               TriggerBurst)
	{
		if (GetAsyncKeyState(TriggerKey))
		{
			if (GetTarget(IClientEntity, IVEngine))
			{
				ClickLeftButton(Button_Press, TriggerBurst);
			}

			else
			{
				ClickLeftButton(Button_Release, TriggerBurst);
			}
		}
		else
		{
			ClickLeftButton(Button_Release, TriggerBurst);
		}
	}

	static bool GetTarget (
		const IClientEntityList* IClientEntity,
		const IVEngineClient*    IVEngine )
	{
		auto LocalPlayer = IClientEntity->GetClientEntity(IVEngine->GetLocalPlayer());

		int EntityIndex = (LocalPlayer->GetCrosshairId() - 1);

		if (EntityIndex > MaxEntityIndex || EntityIndex < 0)
			return false;

		auto TargetPlayer = IClientEntity->GetClientEntity(EntityIndex);

		return (TargetPlayer->GetTeamNum() != LocalPlayer->GetTeamNum() && TargetPlayer->GetHealth() > 0);
	}

	static void ClickLeftButton(const bool & Flags, const int & ClickBurst)
	{
		static bool Click = false;
		switch (Flags)
		{
			case Button_Press:
			{
				if (Click == false)
				{
					mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
					Click = true;
				}
				break;
			}
			case Button_Release:
			{
				if (Click == true)
				{
					bool Release = false;
					if (ClickBurst)
					{
						static auto TickCount = GetTickCount();
						if (GetTickCount() - TickCount > (unsigned int)ClickBurst)
						{
							TickCount = GetTickCount();
							Release = true;
						}
					}
					else
					{
						Release = true;
					}
					if (Release == true)
					{
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						Click = false;
					}
				}
				break;
			}
		}
	}
}