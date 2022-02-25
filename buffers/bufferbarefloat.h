#ifndef BUFFERBAREFLOAT_H
#define BUFFERBAREFLOAT_H

#include <memory>

class BufferBareFloat
{
public:
    typedef std::shared_ptr<BufferBareFloat> Ptr;
    BufferBareFloat(int size);
    ~BufferBareFloat();

    virtual int getSize();
    float getValue(int pos);
    float setValue(int pos, float value);
    float *getBuffer();
private:
    int m_size;
    float *m_buffer;
};

#endif // BUFFERBAREFLOAT_H
