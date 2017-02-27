#pragma once

#include <string>
#include <memory>
#include <map>
#include <vector>

namespace mtr
{
	class VModule;
	
	class ModuleLoader
	{
	public:
		static std::shared_ptr<VModule> load_moodule(std::string name);

	protected:
		static std::map<std::string, std::shared_ptr<VModule>> _cache;
	};
}