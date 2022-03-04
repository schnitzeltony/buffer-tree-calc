#ifndef TCALCCONTAINER_H
#define TCALCCONTAINER_H

#include "calc-components/abstractcalculationcomponent.h"
#include "buffers/buffertemplate.h"

#define CALC_PTR(INTYPE, OUTTYPE) std::shared_ptr<TCalcContainer<INTYPE, OUTTYPE>>

template <class INTYPE, class OUTTYPE>
class TCalcContainer : public AbstractCalculationComponent
{
public:
    TCalcContainer(std::vector<CALC_PTR(INTYPE, OUTTYPE)> inputCalculators,
                   BUFFER_PTR(OUTTYPE) outputBuffer,
                   AbstractAccessStrategy::Ptr accessStrategy) :
        AbstractCalculationComponent(accessStrategy),
        m_inputCalculators(inputCalculators),
        m_outputBuffer(outputBuffer) { }
    virtual void init() override final;
    virtual void destroy() override final;
    BUFFER_PTR(OUTTYPE) getOutputBuffer() { return m_outputBuffer; }
private:
    virtual void doInit() { }
    virtual void doDestroy() { }
    virtual bool doCalc(int sampleCount) override;// final;
    bool calcInputs(int sampleCount);
    std::vector<CALC_PTR(INTYPE, OUTTYPE)> m_inputCalculators;
    BUFFER_PTR(OUTTYPE) m_outputBuffer;
};

#include "tcalccontainerimplement.h"


#endif // TCALCCONTAINER_H
