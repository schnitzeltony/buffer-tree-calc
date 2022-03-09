#ifndef CALCULATORFFTWINVFLOAT_H
#define CALCULATORFFTWINVFLOAT_H

#include "calculatorfftwinv.h"
#include <fftw3.h>

class CalculatorFftwInvFloat : public CalculatorFftwInv<float>
{
public:
    CalculatorFftwInvFloat(CALC_PTR(std::complex<float>) inFft,
                           BUFFER_PTR(float) outReal,
                           AbstractAccessStrategy::Ptr accessStrategy);
    virtual ~CalculatorFftwInvFloat();
    virtual void doCalc(int) override;
    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorFftwInv> createWithOutBuffer(CALC_PTR(std::complex<float>) inFft, int bufferSize)
    {
        return std::make_shared<CalculatorFftwInvFloat>(inFft,
                                                        std::make_shared<BufferTemplate<float>>(bufferSize),
                                                        createAccessStrategy<ACCESS_STRATEGY>());
    }
private:
    fftwf_plan m_fftwPlan = nullptr;
};

#endif // CALCULATORFFTWINVFLOAT_H
