#include "iota/tokenizer.h"
#include <stdlib.h>
#include "iota/token.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

static IotaToken* getToken(IotaTokenizer* tokenizer);
static void eatWhitespace(IotaTokenizer* tokenizer);
static void nextCharacter(IotaTokenizer* tokenizer);

static IotaToken* collectId(IotaTokenizer* tokenizer);
static IotaToken* getKeyword(char* value, size_t length);


IotaTokenizer* iotaTokenizer(const char* code, size_t codeSize) {
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
	if (isalpha(tokenizer->character)) {
		return collectId(tokenizer);
	}

	return 0;
}

static void eatWhitespace(IotaTokenizer* tokenizer) {
	while (tokenizer->character == ' ' && tokenizer->index < tokenizer->codeSize) {
		nextCharacter(tokenizer);
	}
}

static void nextCharacter(IotaTokenizer* tokenizer) {
	tokenizer->index += 1;
	tokenizer->character = tokenizer->code[tokenizer->index];
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

	return iotaTokenNone();
}
