#include "iota/token.h"
#include <stdlib.h>

IotaToken* iotaToken(IotaTokenType type, char* value, size_t length) {
	IotaToken* token = malloc(sizeof(IotaToken));
	token->type = type;
	token->value = value;
	token->length = length;
	
	return token;
}

IotaToken* iotaTokenNone() {
	IotaToken* token = malloc(sizeof(IotaToken));
	token->type = TOKEN_NONE;
	token->value = 0;
	token->length = 0;

	return token;
}
