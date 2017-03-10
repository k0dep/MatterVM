#include "SCommandList.h"
using namespace mtr;
using namespace std;

vector<shared_ptr<ICommand>> SCommandList::command_list = vector<shared_ptr<ICommand>>();

int SCommandList::registre_global_command(std::shared_ptr<ICommand> cmd)
{
	SCommandList::command_list.push_back(cmd);
	return 0;
}
