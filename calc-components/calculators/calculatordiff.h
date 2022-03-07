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
                   AbstractAccessStrategy::Ptr accessStrategy,
                   bool scalarSubtrahend = false);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorDiff<T>> createWithOutBuffer(CALC_PTR(T) minuent, CALC_PTR(T) subtrahent, int bufferSize, bool scalarSubtrahend = false)
    {
        return std::make_shared<CalculatorDiff<T>>(minuent,
                                                   subtrahent,
                                                   std::make_shared<BufferTemplate<T>>(bufferSize),
                                                   createAccessStrategy<ACCESS_STRATEGY>(),
                                                   scalarSubtrahend);
    }
private:
    BUFFER_PTR(T) m_minuentBuffer;
    BUFFER_PTR(T) m_subtrahentBuffer;
    bool m_scalarSubtrahend;
};

#include "calculatordiff_impl.h"

#endif // CALCULATORDIFF_H
