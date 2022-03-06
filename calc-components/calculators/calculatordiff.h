#ifndef CALCULATORDIFF_H
#define CALCULATORDIFF_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T>
class CalculatorDiff : public CalculatorBase<T>
{
public:
    CalculatorDiff(CALC_PTR(T) minuent,
                   CALC_PTR(T) subtrahent,
                   BUFFER_PTR(T) output,
                   AbstractAccessStrategy::Ptr accessStrategy);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorDiff<T>> createWithOutBuffer(CALC_PTR(T) minuent, CALC_PTR(T) subtrahent, int bufferSize)
    {
        return std::make_shared<CalculatorDiff<T>>(minuent,
                                                   subtrahent,
                                                   std::make_shared<BufferTemplate<T>>(bufferSize),
                                                   createAccessStrategy<ACCESS_STRATEGY>());
    }
private:
    BUFFER_PTR(T) m_minuentBuffer;
    BUFFER_PTR(T) m_subtrahentBuffer;
};

#include "calculatordiff_impl.h"

#endif // CALCULATORDIFF_H
