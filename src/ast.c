#include "iota/ast.h"
#include <stdlib.h>
#include <stdio.h>
#include "iota/types.h"

IotaAst* iotaModuleAst(char* name) {
	IotaAst* ast = malloc(sizeof(IotaAst));
	ast->type = AST_MODULE;
	ast->children = iotaList(sizeof(IotaAst));
    ast->name = name;

	return ast;
}

IotaAst* iotaRootAst() {
	IotaAst* ast = malloc(sizeof(IotaAst));
	ast->type = AST_ROOT;
	ast->children = iotaList(sizeof(IotaAst));

	return ast;
}

IotaAst* iotaNoneAst() {
	IotaAst* ast = malloc(sizeof(IotaAst));
	ast->type = AST_NONE;
	ast->children = 0;

	return ast;
}

IotaAst* iotaFunctionAst(char* name) {
	IotaAst* ast = malloc(sizeof(IotaAst));
	ast->type = AST_FUNCTION;
	ast->children = iotaList(sizeof(IotaAst));
    ast->name = name;

	return ast;
}

IotaAst* iotaReturnAst(char* returnValue, IotaNativeType type) {
	IotaAst* ast = malloc(sizeof(IotaAst));
	ast->type = AST_RETURN;
	ast->children = 0;
    ast->value = returnValue;
	ast->valueType = type;
}
