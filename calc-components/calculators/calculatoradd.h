#ifndef CALCULATORADD_H
#define CALCULATORADD_H

#include "calc-components/calculatorbase.h"
#include "buffers/buffertemplate.h"

template <class T>
class CalculatorAdd : public CalculatorBase<T>
{
public:
    CalculatorAdd(CALC_PTR(T) buff1,
                  CALC_PTR(T) buff2,
                  BUFFER_PTR(T) output,
                  AbstractAccessStrategy::Ptr accessStrategy,
                  bool scalarBuff2 = false);
    virtual void doCalc(int sampleCount) override;

    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorAdd<T>> createWithOutBuffer(CALC_PTR(T) buff1, CALC_PTR(T) buff2, int bufferSize, bool scalarBuff2 = false)
    {
        return std::make_shared<CalculatorAdd<T>>(buff1,
                                                  buff2,
                                                  std::make_shared<BufferTemplate<T>>(bufferSize),
                                                  createAccessStrategy<ACCESS_STRATEGY>(),
                                                  scalarBuff2);
    }
private:
    BUFFER_PTR(T) m_buff1;
    BUFFER_PTR(T) m_buff2;
    bool m_scalarBuff2;
};

#include "calculatoradd_impl.h"

#endif // CALCULATORADD_H
