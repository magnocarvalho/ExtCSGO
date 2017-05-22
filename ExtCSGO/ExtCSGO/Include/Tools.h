#pragma once
#include <string>

namespace ExtCSGO::Tools
{
	FILE*        OpenFile(const char* FileName);
	void         CloseFile(FILE* File);
	std::string  ReadString(FILE* File, const char* Name);
	void         GetArrayData(const char* Array, const int & dwOffset, void* buffer);
}