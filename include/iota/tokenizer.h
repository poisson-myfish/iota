#ifndef IOTA_TOKENIZER_H
#define IOTA_TOKENIZER_H
#include "iota/list.h"

typedef struct
{
	char* code;
	size_t codeSize;
	
	char character;
	size_t index;
	
	IotaList* tokens;
} IotaTokenizer;

IotaTokenizer* iotaTokenizer(const char* code, size_t codeSize);
void iotaTokenizerAdvance(IotaTokenizer* tokenizer);
int iotaTokenizerHasNext(IotaTokenizer* tokenizer);

#endif
