#include <Windows.h>
#include <memory>

#include <mtr/ModuleLoader.h>
#include <mtr/VModuleNative.h>
#include <mtr/VModuleBytecode.h>

using namespace mtr;
using namespace std;

std::shared_ptr<VModuleBase> mtr::ModuleLoader::load_moodule(std::string name)
{
	if (_cache.find(name) != _cache.end())
		return _cache[name];

	shared_ptr<VModuleBase> module;

	auto wnd_module = LoadLibrary((path + name + ".dll").c_str());
	if (wnd_module)
		module = shared_ptr<VModuleBase>((VModuleBase*) new VModuleNative(wnd_module, name));
	else
	{
		auto programm = DataTypes::SFileStructure::read((path + name + ".mtrbc").c_str());
		module = shared_ptr<VModuleBase>((VModuleBase*) new VModuleBytecode(programm, name));
	}
	_cache[name] = module;

	return module;
}