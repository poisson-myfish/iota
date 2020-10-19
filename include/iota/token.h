#ifndef IOTA_TOKEN_H
#define IOTA_TOKEN_H
#include <stdlib.h>


typedef enum
{
	TOKEN_NONE,
	TOKEN_NEW, TOKEN_ID, TOKEN_COLON, TOKEN_SEMI,
	TOKEN_INTEGER, TOKEN_FLOAT, TOKEN_FUN, TOKEN_MODULE,
	TOKEN_DOUBLECOLON, TOKEN_CURLYLEFT, TOKEN_CURLYRIGHT,
	TOKEN_RETURN, TOKEN_PARENLEFT, TOKEN_PARENRIGHT
} IotaTokenType;


typedef struct
{
    IotaTokenType type;
	char* value;
	size_t length;
} IotaToken;

IotaToken* iotaToken(IotaTokenType type, char* value, size_t length);
IotaToken* iotaTokenNone();

#endif
