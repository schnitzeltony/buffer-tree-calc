#include "sampletofftfloat.h"

SampleToFftFloat::SampleToFftFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                   BUFFER_PTR(float) input,
                                   BUFFER_PTR(float) output) :
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
