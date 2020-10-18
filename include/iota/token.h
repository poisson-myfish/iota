#ifndef IOTA_TOKEN_H
#define IOTA_TOKEN_H
#include <stdlib.h>

typedef enum
{
	TOKEN_NEW, TOKEN_ID, TOKEN_COLON, TOKEN_SEMI,
	TOKEN_INTEGER
} IotaTokenType;


typedef struct
{
    IotaTokenType type;
	char* value;
	size_t valueSize;
} IotaToken;

IotaToken* iotaToken(IotaTokenType type, char* value, size_t size);

#endif
