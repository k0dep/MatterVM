#include "stdafx.h"
#include <mtr/VMachine.h>
using namespace std;
using namespace mtr;

std::string GetDirectoryName(std::string path)
{
	const size_t last_slash_idx = path.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		return path.substr(0, last_slash_idx + 1);
	}
	return "";
}

void __WriteBytecode(char * file, char * bc, size_t sz)
{
	auto fname = string(TEST_CASE_DIRECTORY) + "test_env\\" + file + ".mtrbc";

	FILE *outFile;

	fopen_s(&outFile, fname.c_str(), "wb");
	fwrite(bc, 1, sz, outFile);
	fclose(outFile);

	auto mod = DataTypes::SFileStructure::read(fname.c_str());
	fopen_s(&outFile, (fname + ".dump").c_str(), "w");
	fprintf(outFile, "%s", mod->str().c_str());
	fclose(outFile);
}