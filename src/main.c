#include <stdio.h>
#include <iota/tokenizer.h>
#include <iota/list.h>
#include <iota/token.h>
#include <string.h>
#include <iota/parser.h>
#include <iota/llvmGenerator.h>

int main() {
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

	IotaParser* parser = iotaParser(tokens);
    while (iotaParserHasNext(parser))
		iotaParserAdvance(parser);

	IotaLLVMGenerator* generator = iotaLLVMGenerator(parser->ast);
	char* bytecode = iotaLLVMGeneratorStart(generator);
	printf("\n%s", bytecode);

	FILE* outfile = fopen("milestone.ll", "w");
	fputs(bytecode, outfile);
}
