#ifndef CALCULATORADD_H
#define CALCULATORADD_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T1_OUT, class T2>
class CalculatorAdd2 : public CalculatorBase<T1_OUT>
{
public:
    CalculatorAdd2(CALC_PTR(T1_OUT) buff1,
                   CALC_PTR(T2) buff2,
                   BUFFER_PTR(T1_OUT) output,
                   AbstractAccessStrategy::Ptr accessStrategy,
                   bool scalarBuff2 = false);

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorAdd2<T1_OUT, T2>> createWithOutBuffer(
            CALC_PTR(T1_OUT) buff1,
            CALC_PTR(T2) buff2,
            int bufferSize, bool
            scalarBuff2 = false);
private:
    void doCalc(int sampleCount);
    void doCalcBuff(int sampleCount, BUFFER_PTR(T1_OUT) outBuff);
    void doCalcScalar(int sampleCount, BUFFER_PTR(T1_OUT) outBuff);
    BUFFER_PTR(T1_OUT) m_buff1;
    BUFFER_PTR(T2) m_buff2;
    bool m_scalarBuff2;
};

template <class T>
class CalculatorAdd : public CalculatorAdd2<T, T>
{
};

#include "implementation-headers/calculatoradd_impl.h"

#endif // CALCULATORADD_H
