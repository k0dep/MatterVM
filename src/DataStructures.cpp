#include "DataStructures.h"
#include <stdexcept>

using namespace mtr;
using namespace mtr::DataTypes;
using namespace std;



shared_ptr<SHeader> mtr::DataTypes::SHeader::read(FILE *file)
{
	if (file == nullptr) throw invalid_argument("file must not be null");
	
	auto head = shared_ptr<SHeader>(new SHeader);	

	bool ok = true;

	ok &= DataHelper::read_16(&head->MagicNumber, file);
	ok &= DataHelper::read_16(&head->CountImports, file);
	ok &= DataHelper::read_32(&head->CountFunctions, file);
	ok &= DataHelper::read_32(&head->CountVarBytes, file);
	ok &= DataHelper::read_32(&head->CountVarWords, file);
	ok &= DataHelper::read_32(&head->CountVarQWords, file);
	ok &= DataHelper::read_32(&head->CountVarCustoms, file);

	if (!ok)
		throw runtime_error("load header from file error");

	return shared_ptr<SHeader>(head);
}

size_t mtr::DataTypes::SHeader::allValuesSize() const
{
	return CountVarBytes + (CountVarWords * 2) + (CountVarQWords * 4);
}


shared_ptr<SImportStructure> mtr::DataTypes::SImportStructure::read(FILE *file)
{
	if (file == nullptr) throw invalid_argument("file must not be null");

	auto import = shared_ptr<SImportStructure>(new SImportStructure);
	
	bool ok = true;
	ok &= DataHelper::read_8(&import->NameLength, file);
	ok &= DataHelper::read_16(&import->Index, file);

	if(!ok)
		throw runtime_error("load Import structure from file error");

	import->Name = shared_ptr<i8>(new i8[import->NameLength]);

	if (fread((void*)import->Name.get(), sizeof(i8), import->NameLength, file) != import->NameLength)
		throw runtime_error("load Import structure from file error");

	return shared_ptr<SImportStructure>(import);
}



shared_ptr<SFunctionStructure> mtr::DataTypes::SFunctionStructure::read(FILE *file)
{
	if (file == nullptr) throw invalid_argument("file must not be null");

	auto func = shared_ptr<SFunctionStructure>(new SFunctionStructure);


	if(!DataHelper::read_32(&func->BytecodeLength, file))
		throw runtime_error("load function structure from file error");

	func->Bytecode = shared_ptr<u8>(new u8[func->BytecodeLength]);
	if (fread((void*)func->Bytecode.get(), sizeof(u8), func->BytecodeLength, file) != func->BytecodeLength)
		throw runtime_error("load function structure from file error");

	return shared_ptr<SFunctionStructure>(func);
}





shared_ptr<STypeStructure> mtr::DataTypes::STypeStructure::read(FILE *file)
{
	if (file == nullptr) throw invalid_argument("file must not be null");

	auto type = shared_ptr<STypeStructure>(new STypeStructure);

	if (!DataHelper::read_8(&type->Length, file))
		throw runtime_error("load type structure from file error");

	type->Array = shared_ptr<u8>(new u8[type->Length]);
	if (fread((void*)type->Array.get(), sizeof(u8), type->Length, file) != type->Length)
		throw runtime_error("load type structure from file error");

	return shared_ptr<STypeStructure>(type);

}




mtr::DataTypes::SFileStructure::SFileStructure(std::shared_ptr<SHeader> header)
{
	Head = header;
	ArrImports = vector<shared_ptr<SImportStructure>>( header->CountImports );
	ArrFunctions = vector<shared_ptr<SFunctionStructure>>( header->CountFunctions );
	ArrValues = shared_ptr<u8>(new u8[ header->allValuesSize() ]);
	ArrCustomValues = vector<shared_ptr<STypeStructure>>( header->CountVarCustoms );
}


//===================================================================================//
// доступ к €чейкам
u8 mtr::DataTypes::SFileStructure::byteValue(u32 index) const
{
	return (ArrValues.get())[index];
}

void mtr::DataTypes::SFileStructure::byteValue(u32 index, u8 newValue)
{
	(ArrValues.get())[index] = newValue;
}

u16 mtr::DataTypes::SFileStructure::wordValue(u32 index) const
{
	auto baseAddr = Head->CountVarBytes + (index * 2);
	return ((u16)(ArrValues.get())[baseAddr] << 8) + (u16)(ArrValues.get())[baseAddr+1];
}

void mtr::DataTypes::SFileStructure::wordValue(u32 index, u16 newValue)
{
	auto baseAddr = Head->CountVarBytes + (index * 2);
	(ArrValues.get())[baseAddr] = (u8)((newValue >> 8) & 0xFF);
	(ArrValues.get())[baseAddr+1] = (u8)(newValue & 0xFF);
}

u32 mtr::DataTypes::SFileStructure::qwordValue(u32 index) const
{
	auto baseAddr = Head->CountVarBytes + (Head->CountVarWords * 2) + (index * 4);
	return ((u32)(ArrValues.get())[baseAddr] << 24)
		+ ((u32)(ArrValues.get())[baseAddr + 1] << 16)
		+ ((u32)(ArrValues.get())[baseAddr + 2] << 8)
		+ (u32)(ArrValues.get())[baseAddr + 3];
}

void mtr::DataTypes::SFileStructure::qwordValue(u32 index, u32 newValue)
{
	auto baseAddr = Head->CountVarBytes + (Head->CountVarWords * 2) + (index * 4);
	(ArrValues.get())[baseAddr] = (u8)((newValue >> 24) & 0xFF);
	(ArrValues.get())[baseAddr + 1] = (u8)((newValue >> 16) & 0xFF);
	(ArrValues.get())[baseAddr + 2] = (u8)((newValue >> 8) & 0xFF);
	(ArrValues.get())[baseAddr + 3] = (u8)(newValue & 0xFF);
}
//===================================================================================//

shared_ptr<SFileStructure> mtr::DataTypes::SFileStructure::read(FILE *file)
{
	if (file == nullptr) throw invalid_argument("file must not be null");

	auto header = SHeader::read( file );
	auto fstruct = shared_ptr<SFileStructure>( new SFileStructure( header ) );

	for (size_t i = 0; i < header->CountImports; i++)
		fstruct->ArrImports[i] = SImportStructure::read(file);

	for (size_t i = 0; i < header->CountFunctions; i++)
		fstruct->ArrFunctions[i] = SFunctionStructure::read(file);

	size_t valSize = header->CountVarBytes + (header->CountVarWords * 2) + (header->CountVarQWords * 4);
	if (fread((char*)fstruct->ArrValues.get(), sizeof(u8), valSize, file) != valSize)
		throw runtime_error("load file structure from file error");

	for (size_t i = 0; i < header->CountVarCustoms; i++)
		fstruct->ArrCustomValues[i] = STypeStructure::read(file);

	return shared_ptr<SFileStructure>(fstruct);
}

std::shared_ptr<SFileStructure> mtr::DataTypes::SFileStructure::read(const char * file_name)
{
	FILE* file;
	fopen_s(&file, file_name, "rb");
	if (file == nullptr) throw runtime_error("can't open file");
	auto res = SFileStructure::read(file);
	fclose(file);
	return std::shared_ptr<SFileStructure>(res);
}





// ================================================================== //



bool mtr::DataTypes::DataHelper::read_8(void * data, FILE * file)
{
	if (file == nullptr) return false;
	if (feof(file) != 0) return false;
	return fread(data, 1, 1, file) == 1;
}




bool mtr::DataTypes::DataHelper::read_16(void * data, FILE * file)
{
	if (file == nullptr) return false;
	if (feof(file) != 0) return false;
	auto res = fread(data, 2, 1, file) == 1;
	u8 tmp = ((u8*)data)[0];
	((u8*)data)[0] = ((u8*)data)[1];
	((u8*)data)[1] = tmp;
	return res;
}

bool mtr::DataTypes::DataHelper::read_32(void * data, FILE * file)
{
	if (file == nullptr) return false;
	if (feof(file) != 0) return false;
	auto res = fread(data, 4, 1, file) == 1;
	u8 t0 = ((u8*)data)[0];
	u8 t1 = ((u8*)data)[1];
	((u8*)data)[0] = ((u8*)data)[3];
	((u8*)data)[1] = ((u8*)data)[2];
	((u8*)data)[2] = t1;
	((u8*)data)[3] = t0;
	return res;
}
