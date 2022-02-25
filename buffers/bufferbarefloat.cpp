#include "bufferbarefloat.h"

BufferBareFloat::BufferBareFloat(int size) :
    m_size(size)
{
    m_buffer = new float[size];
}

BufferBareFloat::~BufferBareFloat()
{
    delete [] m_buffer;
}

int BufferBareFloat::getSize()
{
    return m_size;
}

float *BufferBareFloat::getBuffer()
{
    return m_buffer;
}
