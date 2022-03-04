#ifndef TCALCULATOR_H
#define TCALCULATOR_H

#include "calc-components/abstractcalculationcomponent.h"
#include "buffers/buffertemplate.h"

#define CALC_PTR(INTYPE, OUTTYPE) std::shared_ptr<TCalculator<INTYPE, OUTTYPE>>

template <class INTYPE, class OUTTYPE>
class TCalculator : public AbstractCalculationComponent
{
public:
    TCalculator(std::vector<CALC_PTR(INTYPE, OUTTYPE)> inputCalculators, BUFFER_PTR(OUTTYPE) outputBuffer, AbstractAccessStrategy::Ptr accessStrategy) :
        AbstractCalculationComponent(accessStrategy),
        m_inputCalculators(inputCalculators),
        m_outputBuffer(outputBuffer)
    {
    }
    virtual bool doCalc(int sampleCount) override;
    virtual void init() override;
    virtual void destroy() override;
protected:
    virtual void doInit() {}
    virtual void doDestroy() {}
    std::vector<CALC_PTR(INTYPE, OUTTYPE)> m_inputCalculators;
    BUFFER_PTR(OUTTYPE) m_outputBuffer;
};

#endif // TCALCULATOR_H
