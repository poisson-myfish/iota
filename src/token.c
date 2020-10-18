#include "iota/token.h"
#include <stdlib.h>

IotaToken* iotaToken(IotaTokenType type, char* value, size_t size) {
	IotaToken* token = malloc(sizeof(IotaToken));
	token->type = type;
	token->value = value;
	token->valueSize = size;
	
	return token;
}
