// stdafx.h: включаемый файл для стандартных системных включаемых файлов,
// или включаемых файлов для конкретного проекта, которые часто используются, но
// не часто изменяются
//

#pragma once

#include <SDKDDKVer.h>

// Заголовки CppUnitTest
#include "CppUnitTest.h"


#define TEST_CASE_DIRECTORY GetDirectoryName(__FILE__)
std::string GetDirectoryName(std::string path);

void __WriteBytecode(char * file, char * bc, size_t sz);

#define WRITE_BYTECODE(file, bc) __WriteBytecode(file, bc, sizeof(bc))

// TODO: Установите здесь ссылки на дополнительные заголовки, требующиеся для программы
