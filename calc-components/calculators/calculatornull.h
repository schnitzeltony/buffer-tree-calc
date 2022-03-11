#ifndef CALCULATORNULL_H
#define CALCULATORNULL_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"
#include <memory>

template <class T>
class CalculatorNull : public CalculatorBase<T>
{
public:
    CalculatorNull(BUFFER_PTR(T) output,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        CalculatorBase<T>(std::vector<CalcInterface::Ptr> {}, output, [&](int){ }, accessStrategy)
    {}

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorNull<T>> createWithOutBuffer(int bufferSize)
    {
        return std::make_shared<CalculatorNull<T>>(std::make_shared<BufferTemplate<T>>(bufferSize),
                                                   createAccessStrategy<ACCESS_STRATEGY>());
    }
};



#endif // CALCULATORNULL_H
