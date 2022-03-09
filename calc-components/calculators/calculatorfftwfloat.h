#ifndef CALCULATORFFTFLOAT_H
#define CALCULATORFFTFLOAT_H

#include "calculatorfftw.h"
#include <fftw3.h>

class CalculatorFftwFloat : public CalculatorFftw<float>
{
public:
    CalculatorFftwFloat(CALC_PTR(float) inReal,
                        BUFFER_PTR(std::complex<float>) outFft,
                        AbstractAccessStrategy::Ptr accessStrategy);
    virtual ~CalculatorFftwFloat();
    virtual void doCalc(int) override;
    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorFftw> createWithOutBuffer(CALC_PTR(float) inReal,
                                                               int bufferSize)
    {
        return std::make_shared<CalculatorFftwFloat>(inReal,
                                                     std::make_shared<BufferTemplate<std::complex<float>>>(bufferSize),
                                                     createAccessStrategy<ACCESS_STRATEGY>());
    }
private:
    fftwf_plan m_fftwPlan = nullptr;
};

#endif // CALCULATORFFTFLOAT_H
