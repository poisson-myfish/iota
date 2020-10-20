#ifndef IOTA_AST_H
#define IOTA_AST_H
#include "iota/list.h"

typedef enum
{
	AST_NONE, AST_ROOT,
	AST_MODULE, AST_FUNCTION, AST_RETURN
} IotaAstType;

typedef struct
{
	IotaAstType* type;
	void* ast;
	
	IotaList* children;
} IotaAst;



// The different ASTs
typedef struct
{
	char* moduleName;
} IotaModuleAst;

typedef struct
{
	char* name;
	// TODO: Add the argument list and return type
} IotaFunctionAst;


IotaAst* iotaRootAst();
IotaAst* iotaModuleAst(char* name);

#endif
