#include "iota/tokenizer.h"
#include <stdlib.h>
#include "iota/token.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

IotaToken* tokenizeExpression(IotaTokenizer* tokenizer);
void eatWhitespace(IotaTokenizer* tokenizer);
void nextCharacter(IotaTokenizer* tokenizer);

IotaToken* collectId(IotaTokenizer* tokenizer);


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
	    iotaListAppend(tokenizer->tokens, tokenizeExpression(tokenizer));
		
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
IotaToken* tokenizeExpression(IotaTokenizer* tokenizer) {
	if (isalpha(tokenizer->character)) {
		return collectId(tokenizer);
	}

	return 0;
}

void eatWhitespace(IotaTokenizer* tokenizer) {
	while (tokenizer->character == ' ' && tokenizer->index < tokenizer->codeSize) {
		nextCharacter(tokenizer);
	}
}

void nextCharacter(IotaTokenizer* tokenizer) {
	tokenizer->index += 1;
	tokenizer->character = tokenizer->code[tokenizer->index];
}


// Collectors
IotaToken* collectId(IotaTokenizer* tokenizer) {
	size_t initialIndex = tokenizer->index;

	while (isalnum(tokenizer->character)) {
		nextCharacter(tokenizer);
	}

    size_t idLength = tokenizer->index - initialIndex;
	char* id = malloc(idLength * sizeof(char));
	memcpy(id, &tokenizer->code[initialIndex], idLength);

	return iotaToken(TOKEN_ID, id, idLength);
}
