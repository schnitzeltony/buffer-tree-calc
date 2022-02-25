#include "buffers/bufferbarefloat.h"
#include "buffers/buffervectorint16.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calc-composite/calculationcomposite.h"
#include "calc-composite/leaf-components/sampletofftfloat.h"


int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    BufferBareFloat::Ptr inFloatSamples = std::make_shared<BufferBareFloat>(1024);
    BufferBareFloat::Ptr outFloatFft = std::make_shared<BufferBareFloat>(1024);

    BufferVectorInt16Ptr outInt16Fft = std::make_shared<BufferVectorInt16>(1024);

    AbstractAccessStrategy::Ptr sampleToFftAccess = std::make_shared<SingleThreadedAccessStrategy>();
    AbstractCalculationComponent::Ptr sampleToFft = std::make_shared<SampleToFftFloat>(sampleToFftAccess,
                                                                                       inFloatSamples,
                                                                                       outFloatFft);

    return 0;
}
