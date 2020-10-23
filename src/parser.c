#include "iota/parser.h"
#include <stdlib.h>
#include <stdio.h>

static void nextToken(IotaParser* parser);
static IotaAst* getAst(IotaParser* parser);
static void pushAst(IotaParser* parser, IotaAst* ast);

static IotaAst* collectModuleAst(IotaParser* parser);
static IotaAst* collectFunctionDecl(IotaParser* parser);
static IotaAst* collectReturn(IotaParser* parser);

static void expectSemicolon(IotaParser* parser);


IotaParser* iotaParser(IotaList* tokens) {
	IotaParser* parser = malloc(sizeof(IotaParser));
	parser->tokens = tokens;
	parser->token = tokens->elements[0];
	parser->index = 0;
	parser->ast = iotaRootAst();
	parser->astStack = iotaStack();
	iotaStackPush(parser->astStack, parser->ast);
	
	return parser;
}

int iotaParserHasNext(IotaParser* parser) {
    if (parser->index < parser->tokens->elementCount)
		return 1;

	return 0;
}

void iotaParserAdvance(IotaParser* parser) {
	if (iotaParserHasNext(parser)) {
	    IotaAst* ast = (IotaAst*)iotaStackPeek(parser->astStack);
		if (ast != 0)
			iotaListAppend(ast->children, getAst(parser));

		nextToken(parser);
	}
}


// Private functions
static IotaAst* getAst(IotaParser* parser) {	
	if (parser->token->type == TOKEN_MODULE)
		return collectModuleAst(parser);
	else if (parser->token->type == TOKEN_FUN)
		return collectFunctionDecl(parser);
	else if (parser->token->type == TOKEN_CURLYRIGHT)
	    iotaStackPop(parser->astStack);
	else if (parser->token->type == TOKEN_RETURN)
		return collectReturn(parser);

	return iotaNoneAst();
}

static void nextToken(IotaParser* parser) {
    parser->index += 1;
    parser->token = parser->tokens->elements[parser->index];
}

static void pushAst(IotaParser* parser, IotaAst* ast) {
	iotaStackPush(parser->astStack, (void*)ast);
}

static void expectSemicolon(IotaParser* parser) {
    nextToken(parser);
	if (parser->token->type != TOKEN_SEMI) {
		printf("ERROR: Expected Semicolon(;)\n");
		exit(-1);
	}
}


// Collectors
static IotaAst* collectModuleAst(IotaParser* parser) {
	nextToken(parser);

	IotaAst* ast = iotaModuleAst(parser->token->value);
	pushAst(parser, ast);
    expectSemicolon(parser);
    return ast;
}

static IotaAst* collectFunctionDecl(IotaParser* parser) {
	nextToken(parser);

	if (parser->token->type != TOKEN_ID)
		return iotaNoneAst();  // TODO: Throw an error
	char* name = parser->token->value;
	nextToken(parser);

	if (parser->token->type != TOKEN_DOUBLECOLON)
		return iotaNoneAst();  // TODO: Throw an error
	nextToken(parser);

	IotaNativeType returnType;
	switch (parser->token->type) {
	case TOKEN_T_INT:
	    returnType = IOTA_TYPE_INT_32;
		break;

	default: break;
	}
	nextToken(parser);

	if (parser->token->type != TOKEN_PARENLEFT)
		return iotaNoneAst();  // TODO: Throw an error
	nextToken(parser);
	// TODO: Collect the arguments
	if (parser->token->type != TOKEN_PARENRIGHT)
		return iotaNoneAst();  // TODO: Throw an error
	nextToken(parser);

	if (parser->token->type != TOKEN_CURLYLEFT)
		return iotaNoneAst();  // TODO: Throw an error

	IotaAst* ast = iotaFunctionAst(name, returnType);
	pushAst(parser, ast);

	return ast;
}

static IotaAst* collectReturn(IotaParser* parser) {
	nextToken(parser);
	IotaAst* ast;

	switch (parser->token->type) {
	case TOKEN_INTEGER:
		ast = iotaReturnAst(parser->token->value, IOTA_TYPE_INT_32);
		break;

    default:
		ast = iotaNoneAst();
	}

	expectSemicolon(parser);

	return ast;
}
