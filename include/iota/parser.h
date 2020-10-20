#ifndef IOTA_PARSER_H
#define IOTA_PARSER_H
#include "iota/list.h"
#include "iota/token.h"
#include "iota/ast.h"
#include "iota/stack.h"

typedef struct
{
	IotaList* tokens;
	IotaToken* token;
	size_t index;

	IotaAst* ast;
	IotaStack* astStack;
} IotaParser;

IotaParser* iotaParser(IotaList* tokens);
int iotaParserHasNext(IotaParser* parser);
void iotaParserAdvance(IotaParser* parser);

#endif
