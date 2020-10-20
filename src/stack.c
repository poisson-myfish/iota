#include "iota/stack.h"
#include <stdlib.h>

IotaStack* iotaStack() {
    IotaStack* stack = malloc(sizeof(IotaStack));
	stack->top = -1;

	return stack;
}

int iotaStackPush(IotaStack* stack, void* element) {
    if (!iotaStackIsFull(stack)) {
		stack->top += 1;
		stack->stack[stack->top] = element;
		return 1;
	}

	return 0;
}

void* iotaStackPop(IotaStack* stack) {
	if (!iotaStackIsEmpty(stack)) {
		void* element = stack->stack[stack->top];
		stack->top -= 1;
		return element;
	}

	return 0;
}

void* iotaStackPeek(IotaStack* stack) {
	return stack->stack[stack->top];
}

int iotaStackIsEmpty(IotaStack* stack) {
	if (stack->top == -1)
		return 1;
	
	return 0;
}

int iotaStackIsFull(IotaStack* stack) {
	if (stack->top == IOTA_STACK_SIZE)
		return 1;

	return 0;
}
