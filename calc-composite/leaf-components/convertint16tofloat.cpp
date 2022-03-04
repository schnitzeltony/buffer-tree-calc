#include "convertint16tofloat.h"

ConvertInt16ToBareFloat::ConvertInt16ToBareFloat(AbstractAccessStrategy::Ptr accessStrategy,
                                                 std::shared_ptr<BufferTemplate<int16_t> > input,
                                                 std::shared_ptr<BufferTemplate<float> > output) :
    AbstractCalculationComponent(accessStrategy),
    m_input(input),
    m_output(output)
{
}

bool ConvertInt16ToBareFloat::doCalc(int sampleCount)
{

}
