#include "sampletofftfloat.h"

SampleToFftFloat::SampleToFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                   BufferBareFloat::Ptr input,
                                   BufferBareFloat::Ptr output) :
    AbstractCalculationComponent(accessStrategy),
    m_input(input),
    m_output(output)
{
}

void SampleToFftFloat::init()
{

}

void SampleToFftFloat::destroy()
{

}

bool SampleToFftFloat::doCalc(int sampleCount)
{

}
