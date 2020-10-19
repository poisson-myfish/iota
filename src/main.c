#include <stdio.h>
#include <iota/tokenizer.h>
#include <iota/list.h>
#include <iota/token.h>
#include <string.h>

int main() {
	//	const char* code = "new    variable: 32;\0";

	FILE* file;
	file = fopen("examples/milestone.iota", "r");
	size_t characters = 0;
	char buffer[10000];

	char c;
	while ((c = fgetc(file)) != EOF) {
		buffer[characters] = c;
		characters += 1;
	}
	
	IotaTokenizer* tokenizer = iotaTokenizer(buffer, characters);

	while (iotaTokenizerHasNext(tokenizer)) {
		iotaTokenizerAdvance(tokenizer);
	}

    IotaList* tokens = tokenizer->tokens;

	for (size_t i = 0; i < tokens->elementCount; i++) {
		IotaToken* token = (IotaToken*)tokens->elements[i];
		printf("Value: %s, Type: %i\n", token->value, token->type);
	}
}
