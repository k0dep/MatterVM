#include "VModule.h"
using namespace mtr;

std::vector<std::pair<std::string, u16>> mtr::VModule::require_modules()
{
	return _required_modules;
}

u32 mtr::VModule::function_count() const
{
	return _functions.size();
}

u32 mtr::VModule::register_function(ExecutePtr ptr)
{
	auto ret_code = std::shared_ptr<u8>(new u8[1]{ 0x3 });
	_functions.push_back(std::pair<std::shared_ptr<u8>, ExecutePtr>(ret_code, ptr));
	return _functions.size() - 1;
}

std::pair<std::shared_ptr<u8>, ExecutePtr> mtr::VModule::get_function(u32 index) const
{
	return _functions[index];
}
