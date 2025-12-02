#include "stdafx.h"
#include "VertexBuffer.h"

void VertexBuffer::SetIA()
{
	DEVICECONTEXT->IASetVertexBuffers(0, 1, buffer.GetAddressOf(), &stride, &offset);
}
