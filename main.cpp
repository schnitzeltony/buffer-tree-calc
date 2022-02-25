#include "buffers/bufferbarefloat.h"
#include "buffers/buffervectorint16.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calc-composite/calculationcomposite.h"
#include "calc-composite/leaf-components/sampletofftfloat.h"


/*int main(int argc, char *argv[])
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
}*/

#include <iostream>
#include <thread>
#include <chrono>

static std::chrono::high_resolution_clock::time_point start;
static std::chrono::high_resolution_clock::time_point startedfoo;
static std::chrono::high_resolution_clock::time_point startedbar;

void foo()
{
    using namespace std::chrono;
    startedfoo = high_resolution_clock::now();
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

void bar()
{
    using namespace std::chrono;
    startedbar = high_resolution_clock::now();
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main()
{
    using namespace std::chrono;
    start = high_resolution_clock::now();

    std::cout << "starting first helper...\n";
    std::thread helper1(foo);

    std::cout << "starting second helper...\n";
    std::thread helper2(bar);

    std::cout << "waiting for helpers to finish..." << std::endl;
    helper1.join();
    helper2.join();

    std::cout << "done!\n";


    duration<double> time_span = duration_cast<duration<double>>(startedfoo - start);
    std::cout << "It took " << time_span.count() << " seconds to start foo.\n";
    time_span = duration_cast<duration<double>>(startedbar - start);
    std::cout << "It took " << time_span.count() << " seconds to start bar.\n";
}
