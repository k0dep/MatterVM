#pragma once

#ifndef _MODULELOADER_H_
#define _MODULELOADER_H_


#include <string>
#include <memory>
#include <map>
#include <vector>

#include <mtr/VModuleBase.h>

namespace mtr
{
	class ModuleLoader
	{
	public:
		static std::string path;
		static std::shared_ptr<VModuleBase> load_moodule(std::string name);

	protected:
		static std::map<std::string, std::shared_ptr<VModuleBase>> _cache;
	};
}

#endif // !_MODULELOADER_H_