#include "Netvars.h"
#include "Tools.h"

#include "sdk\IClientEntityList.h"
#include "sdk\IVEngineClient.h"
#include "sdk\Player.h"
namespace ExtCSGO::Netvars
{
	bool InitNetvars()
	{
		//FILE FilePtr;
		//auto *File = &FilePtr;

		//fopen_s(&File, "offsets.cfg", "r");
		auto File = Tools::OpenFile("offsets.cfg");

		if (File == nullptr)
		{
			std::cout << "[error]offsets" << std::endl;
			std::cout << "settings file not found!" << std::endl;
			return false;
		}

		sdk::InitIClientEntityOffsets(File);
		sdk::InitIVEngineOffsets(File);
		sdk::InitPlayerOffsets(File);


		Tools::CloseFile(File);

		return true;
	}
}