#include "Engine.h"
#include "Engine\Memory.h"

#define LIST_MODULES_32BIT 0x1
#define LIST_MODULES_64BIT 0x2
#define LIST_MODULES_ALL 0x3
namespace ExtCSGO::Engine
{
	using namespace sdk;
	static Process*             m_Process;
	static Module*              m_ClientDLL;
	static Module*              m_EngineDLL;
	static IVEngineClient*      m_IVEngineClient;
	static IClientEntityList*   m_IClientEntity;

	static bool IsHandleValid();
	static bool IsModuleValid();

	void StartEngine(const std::string & GamePath, const std::string & LaunchOptions)
	{
		m_Process = new Process
		(
			GamePath.c_str(),
			"csgo.exe",
			"Valve001",
			LaunchOptions.c_str()
		);

		m_ClientDLL = new Module("client.dll", LIST_MODULES_32BIT);

		m_EngineDLL = new Module("engine.dll", LIST_MODULES_32BIT);

		m_IVEngineClient = new IVEngineClient();

		m_IClientEntity = new IClientEntityList();
	}

	void ShutdownEngine()
	{
		delete m_IClientEntity;
		delete m_IVEngineClient;
		delete m_EngineDLL;
		delete m_ClientDLL;
		delete m_Process;
	}

	IClientEntityList* GetIClientEnt()
	{
		return m_IClientEntity;
	}

	IVEngineClient* GetIVEngine()
	{
		return m_IVEngineClient;
	}

	void UpdateEngine()
	{
		if (!IsHandleValid())
		{
			m_ClientDLL->Reset();
			m_EngineDLL->Reset();
			m_Process->Init();
		}
		else
		{
			m_ClientDLL->Init(m_Process->GetHandle());
			m_EngineDLL->Init(m_Process->GetHandle());

			if (IsModuleValid())
			{
				std::cout << "Process Found! Handle:" << m_Process->GetHandle() << std::endl;
			}
		}
		
	}

	void UpdateEvents()
	{
		m_IClientEntity->Update(m_Process, m_ClientDLL);
		m_IVEngineClient->Update(m_Process, m_EngineDLL);
	}

	bool IsValid()
	{
		if (!IsHandleValid())
			return false;

		if (!IsModuleValid())
			return false;

		return true;
	}

	static bool IsHandleValid()
	{
		return m_Process->IsValid(PROCESS_HANDLE);
	}

	static bool IsModuleValid()
	{
		if (!m_ClientDLL->IsValid())
			return false;

		if (!m_EngineDLL->IsValid())
			return false;

		return true;
	}
}

