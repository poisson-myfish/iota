#include "iota/tokenizer.h"
#include <stdlib.h>
#include "iota/token.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

static IotaToken* getToken(IotaTokenizer* tokenizer);
static void eatWhitespace(IotaTokenizer* tokenizer);
static void nextCharacter(IotaTokenizer* tokenizer);
static char peekChar(IotaTokenizer* tokenizer);

static IotaToken* collectId(IotaTokenizer* tokenizer);
static IotaToken* getKeyword(char* value, size_t length);
static IotaToken* collectColon(IotaTokenizer* tokenizer);
static IotaToken* collectCurly(IotaTokenizer* tokenizer);
static IotaToken* collectParen(IotaTokenizer* tokenizer);
static IotaToken* collectNumber(IotaTokenizer* tokenizer);

IotaTokenizer* iotaTokenizer(char* code, size_t codeSize) {
	IotaTokenizer* tokenizer = malloc(sizeof(IotaTokenizer));
	tokenizer->code = code;
	tokenizer->character = code[0];
	tokenizer->index = 0;
	tokenizer->tokens = iotaList(sizeof(IotaToken));
	tokenizer->codeSize = codeSize;

    return tokenizer;
}

void iotaTokenizerAdvance(IotaTokenizer* tokenizer) {
	if (tokenizer->index < tokenizer->codeSize && tokenizer->character != '\0') {
		eatWhitespace(tokenizer);
		
	    iotaListAppend(tokenizer->tokens, getToken(tokenizer));

		if (tokenizer->character == ';') {
			iotaListAppend(tokenizer->tokens, iotaToken(TOKEN_SEMI, ";", 1));
		}
		
		nextCharacter(tokenizer);
		eatWhitespace(tokenizer);
	}
}

int iotaTokenizerHasNext(IotaTokenizer* tokenizer) {
	if (tokenizer->index < tokenizer->codeSize && tokenizer->character != '\0') {
		return 1;
	}
	return 0;
}


// Private Functions
static IotaToken* getToken(IotaTokenizer* tokenizer) {
	if (isalpha(tokenizer->character))
		return collectId(tokenizer);
	else if (tokenizer->character == ':')
		return collectColon(tokenizer);
	else if (tokenizer->character == '{' || tokenizer->character == '}')
		return collectCurly(tokenizer);
	else if (tokenizer->character == '(' || tokenizer->character == ')')
		return collectParen(tokenizer);
	else if (isdigit(tokenizer->character))
		return collectNumber(tokenizer);

	return iotaTokenNone();
}

static void eatWhitespace(IotaTokenizer* tokenizer) {
	char character = tokenizer->character;
	while (character == ' ' || character == '\n' || character == '\t'){
		nextCharacter(tokenizer);
		character = tokenizer->character;
	}
}

static void nextCharacter(IotaTokenizer* tokenizer) {
	tokenizer->index += 1;
	tokenizer->character = tokenizer->code[tokenizer->index];
}

static char peekChar(IotaTokenizer* tokenizer) {
	return tokenizer->code[tokenizer->index + 1];
}


// Collectors
static IotaToken* collectId(IotaTokenizer* tokenizer) {
	size_t initialIndex = tokenizer->index;

	while (isalnum(tokenizer->character)) {
		nextCharacter(tokenizer);
	}

    size_t idLength = tokenizer->index - initialIndex;
	char* id = malloc(idLength * sizeof(char));
	memcpy(id, &tokenizer->code[initialIndex], idLength);

	IotaToken* keyword = getKeyword(id, idLength);
	if (keyword->type != TOKEN_NONE)
		return keyword;
	else
		free(keyword);

	return iotaToken(TOKEN_ID, id, idLength);
}

static IotaToken* getKeyword(char* value, size_t length) {
	if (strcmp(value, "new") == 0)
   		return iotaToken(TOKEN_NEW, value, length);
	else if (strcmp(value, "fun") == 0)
		return iotaToken(TOKEN_FUN, value, length);
	else if (strcmp(value, "module") == 0)
		return iotaToken(TOKEN_MODULE, value, length);
	else if (strcmp(value, "return") == 0)
		return iotaToken(TOKEN_RETURN, value, length);

	else if (strcmp(value, "Int") == 0)
		return iotaToken(TOKEN_T_INT, value, length);

	return iotaTokenNone();
}

static IotaToken* collectColon(IotaTokenizer* tokenizer) {
	if (peekChar(tokenizer) == ':') {
		nextCharacter(tokenizer);
		return iotaToken(TOKEN_DOUBLECOLON, "::", 2);
	}

	return iotaToken(TOKEN_COLON, ":", 1);
}

static IotaToken* collectCurly(IotaTokenizer* tokenizer) {
    if (tokenizer->character == '{')
		return iotaToken(TOKEN_CURLYLEFT, "{", 1);

	return iotaToken(TOKEN_CURLYRIGHT, "}", 1);
}

static IotaToken* collectParen(IotaTokenizer* tokenizer) {
	if (tokenizer->character == '(')
		return iotaToken(TOKEN_PARENLEFT, "(", 1);

	return iotaToken(TOKEN_PARENRIGHT, ")", 1);
}

static IotaToken* collectNumber(IotaTokenizer* tokenizer) {
	size_t initialIndex = tokenizer->index;
	
	while (isdigit(tokenizer->character))
		nextCharacter(tokenizer);

	// TODO: Check for floats

	size_t length = tokenizer->index - initialIndex;
	char* number = malloc(length * sizeof(char));
	memcpy(number, &tokenizer->code[initialIndex], length);

	return iotaToken(TOKEN_INTEGER, number, strlen(number));
}
