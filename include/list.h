#ifndef IOTA_LIST_H
#define IOTA_LIST_H

typedef struct
{
	size_t elementSize;
	size_t elementCount;
	void* elements;
} IotaList;

IotaList* iotaList(size_t elementSize);
void iotaListAppend(IotaList* list, void* element);

#endif
