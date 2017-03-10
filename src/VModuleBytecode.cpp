#include "VMachine.h"
#include "VModuleBytecode.h"
#include <string.h>

using namespace mtr;
using namespace mtr::DataTypes;
using namespace std;

VModuleBytecode::VModuleBytecode(shared_ptr<SFileStructure> data, std::string name)
{
	_data = data;
	_name = name;

	_required_modules = vector<pair<string, u16>>();

	for each (auto item in data->ArrImports)
	{
		string rname = string(item->Name.get(), item->NameLength);
		_required_modules.push_back(pair<string, u16>(rname, item->Index));
	}
}

u32 VModuleBytecode::function_count() const
{
	return _data->Head->CountFunctions;
}

shared_ptr<u8> VModuleBytecode::get_function(u32 index, VMachine * machine) const
{
	return _data->ArrFunctions[index]->Bytecode;
}
