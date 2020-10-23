#include "iota/llvmGenerator.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void bufferWrite(IotaLLVMGenerator* generator, char* text);


static void generateModuleAst(IotaLLVMGenerator* generator, IotaAst* mod);
static void generateFunctionAst(IotaLLVMGenerator* generator, IotaAst* fun);
static void generateReturnAst(IotaLLVMGenerator* generator, IotaAst* ret);

static void writeType(IotaLLVMGenerator* generator, IotaNativeType type);

IotaLLVMGenerator* iotaLLVMGenerator(IotaAst* ast) {
	IotaLLVMGenerator* generator = malloc(sizeof(IotaLLVMGenerator));
	generator->ast = ast;
	generator->textBuffer = malloc(sizeof(char) * 100);
	generator->bufferSize = 100;
	generator->bufferIndex = 0;

	return generator;
}

char* iotaLLVMGeneratorStart(IotaLLVMGenerator* generator) {
	for (size_t index = 0; index < generator->ast->children->elementCount; index++) {
		IotaAst* ast = generator->ast->children->elements[index];
		switch (ast->type) {
		case AST_MODULE:
			generateModuleAst(generator, ast);
			break;

		default: break;
		}
	}
	
	return generator->textBuffer;
}


// Private functions
static void bufferWrite(IotaLLVMGenerator* generator, char* text) {
	if (generator->bufferSize < generator->bufferIndex + strlen(text)) {
		generator->textBuffer = realloc(generator->textBuffer, sizeof(char) * 100 + generator->bufferSize);
		generator->bufferSize += 100;
	}
	
	sprintf(generator->textBuffer + generator->bufferIndex, "%s", text);
	generator->bufferIndex += strlen(text);
}

static void writeType(IotaLLVMGenerator* generator, IotaNativeType type) {
	switch (type) {
    case IOTA_TYPE_INT_32:
		bufferWrite(generator, "i32 ");
		break;

	default: break;
	}
}

// Generators
static void generateModuleAst(IotaLLVMGenerator* generator, IotaAst* mod) {
    // Do something with modules
	
	for (size_t index = 0; index < mod->children->elementCount; index++) {
		IotaAst* ast = mod->children->elements[index];

		switch (ast->type) {
		case AST_FUNCTION:
			generateFunctionAst(generator, ast);
			break;

		default: break;
		}
	}
}

static void generateFunctionAst(IotaLLVMGenerator* generator, IotaAst* fun) {
	bufferWrite(generator, "define ");
	
	writeType(generator, fun->valueType);

	bufferWrite(generator, "@");
	bufferWrite(generator, fun->name);
	bufferWrite(generator, "()");  // TODO: Scan argument list
	bufferWrite(generator, " {\n");

    for (size_t index = 0; index < fun->children->elementCount; index++) {
		IotaAst* ast = fun->children->elements[index];

		switch (ast->type) {
		case AST_RETURN:
			generateReturnAst(generator, ast);
			break;

		default: break;
		}
	}

	bufferWrite(generator, "\n}");
}

static void generateReturnAst(IotaLLVMGenerator* generator, IotaAst* ret) {
	bufferWrite(generator, "ret ");
	writeType(generator, ret->valueType);

	// TODO: This is not always the case. We could return variables. Tune this
	bufferWrite(generator, ret->value);
}
