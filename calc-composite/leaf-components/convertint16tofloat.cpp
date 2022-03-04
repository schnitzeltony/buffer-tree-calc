#include "convertint16tofloat.h"

ConvertInt16ToBareFloat::ConvertInt16ToBareFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                                 BufferVectorInt16Ptr input,
                                                 BufferBareFloat::Ptr output) :
    AbstractCalculationComponent(accessStrategy),
    m_input(input),
    m_output(output)
{
}

bool ConvertInt16ToBareFloat::doCalc(int sampleCount)
{

}
