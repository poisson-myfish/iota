#ifndef IOTA_STACK_H
#define IOTA_STACK_H

#define IOTA_STACK_SIZE 100

typedef struct
{
	void* stack[IOTA_STACK_SIZE];
    int top;
} IotaStack;

IotaStack* iotaStack();
int iotaStackPush(IotaStack* stack, void* element);
void* iotaStackPop(IotaStack* stack);
void* iotaStackPeek(IotaStack* stack);

int iotaStackIsEmpty(IotaStack* stack);
int iotaStackIsFull(IotaStack* stack);


#endif
