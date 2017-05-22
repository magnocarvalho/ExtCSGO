#include "Tools.h"

namespace ExtCSGO::Tools
{
	static bool ReadFile(FILE* File, char* Buffer, const size_t BufferSize);
	FILE* OpenFile(const char* FileName)
	{
		FILE   File;
		auto*  FilePtr = &File;
		return !(fopen_s(&FilePtr, FileName, "r")) ? FilePtr : nullptr;
	}

	void CloseFile(FILE* File)
	{
		fclose(File);
	}

	std::string ReadString(FILE* File, const char* Name)
	{
		char str[260];
		std::string StrString;
		while (ReadFile(File, str, 260))
		{
			StrString = str;
			if (StrString.find(Name) != std::string::npos)
			{
				StrString.erase(StrString.begin(), StrString.begin() + strlen(Name));
				break;
			}
		}

		return StrString;
	}

	static bool ReadFile(FILE* File, char* Buffer, const size_t BufferSize)
	{
		return fgets(Buffer, (int)BufferSize, File) > nullptr;
	}

	void GetArrayData(const char* Array, const int & dwOffset, void* buffer)
	{
		*(void**)buffer = *(void**)(Array + dwOffset);
	}
}