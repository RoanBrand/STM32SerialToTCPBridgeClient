#include "ByteBuffer.h"

static int availablePublic(const void* b)
{
	ByteBuffer* self = (ByteBuffer*)b;

	if (self->isFull)
	{
		return 256;
	}
	if (self->pT >= self->pH)
	{
		return (int)(self->pT - self->pH);
	} else
	{
		return 256 - (int)(self->pH - self->pT);
	}
}

// Constructor
void newByteBuffer(ByteBuffer* b)
{
	b->pH = 0;
	b->pT = 0;
	b->isFull = false;
	b->available = availablePublic;
}
