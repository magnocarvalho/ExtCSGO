#include "ExtCSGO.h"

#include "Netvars.h"
#include "Engine.h"

#include "Features\Features.h"
#include "Tools.h"




namespace ExtCSGO
{
	static std::string      m_GamePath;
	static std::string      m_LaunchOptions;
	static int              m_AimKey;
	static float            m_AimFov;
	static int              m_AimSmooth;
	static float            m_Sensitivity;
	static int              m_TriggerKey;
	static int              m_TriggerBurst;
	static bool             m_Enabled = false;

	static void             UpdateThread();
	static bool             ConsoleIsRunning();
	static bool             FeaturesEnabled();
	static void             EnableFeatures(const bool & v);
	static bool             LoadSettings();

	bool Start()
	{
		if (!LoadSettings())
		{
			return false;
		}

		if (!Netvars::InitNetvars())
		{
			return false;
		}

		Engine::StartEngine(m_GamePath, m_LaunchOptions);

		auto hUpdateThread = CreateThread
		(
			nullptr,
			0,
			(LPTHREAD_START_ROUTINE)UpdateThread,
			nullptr,
			0,
			nullptr
		);

		while (ConsoleIsRunning())
		{
			Sleep(1);
			if (FeaturesEnabled())
			{
				if (Engine::IsValid())
				{
					Features::Aimbot
					(
						Engine::GetIClientEnt(),
						Engine::GetIVEngine(),
						m_AimKey,
						m_AimFov,
						m_AimSmooth,
						m_Sensitivity
					);

					Features::Triggerbot
					(
						Engine::GetIClientEnt(),
						Engine::GetIVEngine(),
						m_TriggerKey,
						m_TriggerBurst
					);
				}
			}
		}
		TerminateThread(hUpdateThread, EXIT_SUCCESS);
		CloseHandle(hUpdateThread);



		return true;
	}

	static void UpdateThread()
	{
		while (true)
		{
			if (FeaturesEnabled())
			{
				if (Engine::IsValid())
				{
					Engine::UpdateEvents();
				}
				else
				{
					#ifdef _DEBUG
					#else
					Sleep(5000);
					#endif
					Engine::UpdateEngine();
				}
			}

			if (GetAsyncKeyState(VK_INSERT) & 1)
			{
				EnableFeatures(!FeaturesEnabled());
			}
		}
		return ExitThread(EXIT_SUCCESS);
	}

	void Shutdown()
	{
		Engine::ShutdownEngine();
	}

	static bool FeaturesEnabled()
	{
		return m_Enabled;
	}

	static void EnableFeatures(const bool & v)
	{
		m_Enabled = v;
	}

	static bool LoadSettings()
	{
		auto File = Tools::OpenFile("config.cfg");

		if (File == nullptr)
		{
			std::cout << "[error]settings" << std::endl;
			std::cout << "settings file not found!" << std::endl;
			return false;
		}

		m_GamePath = Tools::ReadString(File, "GamePath=");
		m_LaunchOptions = Tools::ReadString(File, "LaunchOptions=");
		m_AimKey = std::stoi(Tools::ReadString(File, "AimKey="));
		m_AimFov = std::stof(Tools::ReadString(File, "AimFov="));
		m_AimSmooth = std::stoi(Tools::ReadString(File, "AimSmooth="));
		m_Sensitivity = std::stof(Tools::ReadString(File, "Sensitivity="));
		m_TriggerKey = std::stoi(Tools::ReadString(File, "TriggerKey="));
		m_TriggerBurst = std::stoi(Tools::ReadString(File, "TriggerBurst="));

		Tools::CloseFile(File);

		return true;
	}

	static DWORD UpdateMessage = 0;
	static BOOL WINAPI ConsoleHandlerRoutine(DWORD dwCtrlType)
	{
		UpdateMessage = dwCtrlType;
		return (dwCtrlType == CTRL_CLOSE_EVENT) ? TRUE : FALSE;
	}

	static bool ConsoleIsRunning()
	{
		static auto ConHandler = SetConsoleCtrlHandler(ConsoleHandlerRoutine, TRUE);
		return (UpdateMessage != CTRL_CLOSE_EVENT);
	}
}