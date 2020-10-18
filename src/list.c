#include "iota/list.h"

IotaList* iotaList(size_t elementSize) {
	IotaList* list = malloc(sizeof(IotaList));
	list->elementSize = elementSize;
	list->elementCount = 0;
	list->elements = malloc(elementSize);
}

void iotaListAppend(IotaList* list, void* element) {
	size_t elementSize = list->elementSize;
	
	list->elementCount += 1;
	list->elements = realloc(list->elements, elementSize * list->elementCount + elementSize);
	list->elements[list->elementCount - 1] = element;
}
