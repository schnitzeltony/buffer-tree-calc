#include "buffers/buffertemplate.h"
#include "access-strategies/abstractaccessstrategy.h"
#include "access-strategies/singlethreadedaccessstrategy.h"
#include "calc-components/calculators/convertfloattoint16.h"
#include "calc-components/calculators/nullcomponent.h"
#include "calc-components/calculators/calculatorfftfloat.h"

int main()
{
    BUFFER_PTR(float) setPoints = std::make_shared<BufferTemplate<float>>(1024);
    CALC_PTR(float, float) nullSetPointCalc =
            std::make_shared<NullComponent<float>>(createAccessStrategy<SingleThreadedAccessStrategy>(), setPoints);

    BUFFER_PTR(float) actualInput = std::make_shared<BufferTemplate<float>>(1024);
    CALC_PTR(float, float) nullActualInput =
            std::make_shared<NullComponent<float>>(createAccessStrategy<SingleThreadedAccessStrategy>(), actualInput);

    BUFFER_PTR(float) actualFFt = std::make_shared<BufferTemplate<float>>(1024);
    AbstractAccessStrategy::Ptr fftCalcAccess = std::make_shared<SingleThreadedAccessStrategy>();
    CalculatorFftFloat fftCalc(fftCalcAccess, nullActualInput, actualFFt);

    fftCalc.init();

    fftCalc.prepareCalc();
    fftCalc.tryStartCalc(5);



    BUFFER_PTR(int16_t) regulatorOut = std::make_shared<BufferTemplate<int16_t>>(1024);
    BUFFER_PTR(float) regulatorOutFloat = std::make_shared<BufferTemplate<float>>(1024);

    AbstractAccessStrategy::Ptr finalFloatToInt16Access = std::make_shared<SingleThreadedAccessStrategy>();
    ConvertFloatToInt16 finalFloatToInt16(finalFloatToInt16Access, nullptr, regulatorOut);




    BUFFER_PTR(float) outFloatFft = std::make_shared<BufferTemplate<float>>(1024);


    return 0;
}

/*#include <iostream>
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
*/
