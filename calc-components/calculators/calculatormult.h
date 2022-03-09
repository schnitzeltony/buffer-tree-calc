#ifndef CALCULATORMULT_H
#define CALCULATORMULT_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T1_OUT, class T2>
class CalculatorMult2 : public CalculatorBase<T1_OUT>
{
public:
    CalculatorMult2(CALC_PTR(T1_OUT) buff1,
                    CALC_PTR(T2) buff2,
                    BUFFER_PTR(T1_OUT) output,
                    AbstractAccessStrategy::Ptr accessStrategy,
                    bool scalarBuff2 = false);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorMult2<T1_OUT, T2>> createWithOutBuffer(CALC_PTR(T1_OUT) buff1,
                                                                            CALC_PTR(T2) buff2,
                                                                            int bufferSize,
                                                                            bool scalarBuff2 = false);
private:
    BUFFER_PTR(T1_OUT) m_buff1;
    BUFFER_PTR(T2) m_buff2;
    bool m_scalarBuff2;
};

template <class T>
class CalculatorMult : public CalculatorMult2<T, T>
{
};

#include "calculatormult_impl.h"

#endif // CALCULATORMULT_H
