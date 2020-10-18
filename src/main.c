#include <stdio.h>
#include <iota/tokenizer.h>
#include <iota/list.h>
#include <iota/token.h>
#include <string.h>

int main() {
	const char* code = "new    variable: 32;\0";

	IotaTokenizer* tokenizer = iotaTokenizer(code, strlen(code));

	while (iotaTokenizerHasNext(tokenizer)) {
		iotaTokenizerAdvance(tokenizer);
	}
	IotaToken* token = tokenizer->tokens->elements[1];
	printf("'%s'\n", token->value);
}
