#include "VModuleBase.h"
using namespace mtr;

std::vector<std::pair<std::string, u16>> mtr::VModuleBase::require_modules()
{
	return _required_modules;
}

std::string mtr::VModuleBase::get_name() const
{
	return _name;
}
