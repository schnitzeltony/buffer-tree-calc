#ifndef CALCULATORDIFF_H
#define CALCULATORDIFF_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T1_OUT, class T2>
class CalculatorDiff2 : public CalculatorBase<T1_OUT>
{
public:
    CalculatorDiff2(CALC_PTR(T1_OUT) minuent,
                    CALC_PTR(T2) subtrahent,
                    BUFFER_PTR(T1_OUT) output,
                    AbstractAccessStrategy::Ptr accessStrategy,
                    bool scalarSubtrahend = false);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorDiff2<T1_OUT, T2>> createWithOutBuffer(CALC_PTR(T1_OUT) minuent,
                                                                            CALC_PTR(T2) subtrahent,
                                                                            int bufferSize,
                                                                            bool scalarSubtrahend = false);
private:
    BUFFER_PTR(T1_OUT) m_minuentBuffer;
    BUFFER_PTR(T2) m_subtrahentBuffer;
    bool m_scalarSubtrahend;
};

template <class T>
class CalculatorDiff : public CalculatorDiff2<T, T>
{
};

#include "implementation-headers/calculatordiff_impl.h"

#endif // CALCULATORDIFF_H
