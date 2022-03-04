#ifndef BUFFERTEMPLATE_H
#define BUFFERTEMPLATE_H

#include <memory>
#include <cstddef>
#include <vector>

#define BUFFER_PTR(T) std::shared_ptr<BufferTemplate<T>>

template <class T, class Allocator = std::allocator<T>>
class BufferTemplate
{
public:
    BufferTemplate(std::size_t size, const Allocator& alloc = Allocator()) :
        m_buffer(size, alloc)
    {
    };

private:
    std::vector<T, Allocator> m_buffer;
};




#endif // BUFFERTEMPLATE_H
