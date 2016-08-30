/*
 * Simple, small, 8-bit aligned buffer
 */

#ifndef BYTEBUFFER_H_
#define BYTEBUFFER_H_

#include <stdbool.h>
#include <stdint.h>

typedef struct ByteBuffer_t
{
	uint8_t Buf[256];
	uint8_t pH;
	uint8_t pT;
	bool isFull;

	int (*available)(const void* b);
} ByteBuffer;

// Constructor
void newByteBuffer(ByteBuffer* b);

#endif
