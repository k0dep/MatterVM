#include "DataStructures.h"
#include <istream>

using namespace mtr::DataTypes;
using namespace std;


SHeader * mtr::DataTypes::SHeader::read(std::istream & stream)
{
	auto head = new SHeader;
	stream.read((char*)head, sizeof(SHeader));
	return head;
}


SImportStructure * mtr::DataTypes::SImportStructure::read(std::istream & stream)
{
	auto import = new SImportStructure;

	stream.read((char*)&import->NameLength, sizeof(u16));
	stream.read((char*)&import->Index, sizeof(u8));
	import->Name = new i8[import->NameLength];
	stream.read((char*)import->Name, sizeof(u8) * import->NameLength);

	return import;
}


SFunctionStructure * mtr::DataTypes::SFunctionStructure::read(std::istream & stream)
{
	auto func = new SFunctionStructure;

	stream.read((char*)&func->BytecodeLength, sizeof(u32));
	stream.read((char*)func->Bytecode, sizeof(u8) * func->BytecodeLength);

	return func;
}


STypeStructure * mtr::DataTypes::STypeStructure::read(std::istream & stream)
{
	auto type = new STypeStructure;

	stream.read((char*)&type->Length, sizeof(u8));
	stream.read((char*)type->Array, sizeof(u8) * type->Length);

	return type;
}

SFileStructure * mtr::DataTypes::SFileStructure::read(std::istream & stream)
{
	auto header = SHeader::read(stream);
	auto fstruct = new SFileStructure();

	size_t valSize = header->CountVarBytes + (header->CountVarWords * 2) + (header->CountVarQWords * 4);

	fstruct->Head = header;
	fstruct->ArrImports = new SImportStructure*[header->CountImports];
	fstruct->ArrFunctions = new SFunctionStructure*[header->CountFunctions];
	fstruct->ArrValues = new u8[valSize];
	fstruct->ArrCustomValues = new STypeStructure*[header->CountVarCustoms];

	for (size_t i = 0; i < header->CountImports; i++)
	{
		fstruct->ArrImports[i] = SImportStructure::read(stream);
	}

	for (size_t i = 0; i < header->CountFunctions; i++)
	{
		fstruct->ArrFunctions[i] = SFunctionStructure::read(stream);
	}

	stream.read((char*)fstruct->ArrValues, valSize);

	for (size_t i = 0; i < header->CountVarCustoms; i++)
	{
		fstruct->ArrCustomValues[i] = STypeStructure::read(stream);
	}

	return fstruct;
}
