#ifndef IOTA_LLVM_GENERATOR_H
#define IOTA_LLVM_GENERATOR_H
#include "iota/ast.h"
#include "iota/stack.h"

typedef struct
{
	IotaAst* ast;
	
	char* textBuffer;
	size_t bufferSize;
	size_t bufferIndex;
} IotaLLVMGenerator;

IotaLLVMGenerator* iotaLLVMGenerator(IotaAst* ast);
char* iotaLLVMGeneratorStart(IotaLLVMGenerator* generator);


#endif
