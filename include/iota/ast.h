#ifndef IOTA_AST_H
#define IOTA_AST_H
#include "iota/list.h"
#include "iota/types.h"

typedef enum
{
	AST_NONE, AST_ROOT,
	AST_MODULE, AST_FUNCTION, AST_RETURN
} IotaAstType;

typedef struct
{
	IotaAstType type;

	char* name;
	char* value;
	IotaNativeType valueType;
	
	IotaList* children;
} IotaAst;


IotaAst* iotaNoneAst();
IotaAst* iotaRootAst();
IotaAst* iotaModuleAst(char* name);
IotaAst* iotaFunctionAst(char* name, IotaNativeType type);
IotaAst* iotaReturnAst(char* returnValue, IotaNativeType type);

#endif
