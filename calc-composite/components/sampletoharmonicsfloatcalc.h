#ifndef SAMPLETOHARMONICSFLOATCALC_H
#define SAMPLETOHARMONICSFLOATCALC_H

#include "calc-composite/calculationnode.h"
#include "buffercalcbrainstorming.h"

class SampleToHarmonicsFloatCalc : public ICalcNodeComponents, public AbstractCalculationComponent
{
public:
    SampleToHarmonicsFloatCalc(AbstractAccessStrategy::Ptr accessStrategy,
                     ConreteBufferFloatVectorPtr input,
                     ConreteBufferFloatVectorPtr output);
    virtual std::vector<AbstractCalculationComponent *> getInputComponents() override;
    virtual AbstractCalculationComponent *getOutputComponent() override;
    virtual void init() override;
    virtual void destroy() override;
    virtual bool doCalc(int subBufferNo) override;
private:
    ConreteBufferFloatVectorPtr m_input;
    ConreteBufferFloatVectorPtr m_output;
};

#endif // SAMPLETOHARMONICSFLOATCALC_H
