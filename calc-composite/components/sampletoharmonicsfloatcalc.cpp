#include "sampletoharmonicsfloatcalc.h"

SampleToHarmonicsFloatCalc::    SampleToHarmonicsFloatCalc(AbstractAccessStrategy::Ptr accessStrategy,
                                                           ConreteBufferFloatVectorPtr input,
                                                           ConreteBufferFloatVectorPtr output) :
    AbstractCalculationComponent(accessStrategy),
    m_input(input),
    m_output(output)
{
}

std::vector<AbstractCalculationComponent *> SampleToHarmonicsFloatCalc::getInputComponents()
{
    return std::vector<AbstractCalculationComponent *> {m_input.get()};
}

AbstractCalculationComponent *SampleToHarmonicsFloatCalc::getOutputComponent()
{
    return m_output.get();
}

void SampleToHarmonicsFloatCalc::init()
{

}

void SampleToHarmonicsFloatCalc::destroy()
{

}

bool SampleToHarmonicsFloatCalc::doCalc(int subBufferNo)
{

}
