#ifndef CALCULATORFFTFLOAT_H
#define CALCULATORFFTFLOAT_H

#include "calculatorfftw.h"
#include "buffers/buffertemplate.h"
#include <fftw3.h>

class CalculatorFftwFloat : public CalculatorFftw<float>
{
public:
    CalculatorFftwFloat(CALC_PTR(float) in,
                        BUFFER_PTR(float) out,
                        AbstractAccessStrategy::Ptr accessStrategy,
                        bool inverseFft);
    virtual ~CalculatorFftwFloat();
    virtual void doCalc(int) override;
    template <typename ACCESS_STRATEGY>
    static std::shared_ptr<CalculatorFftw> createWithOutBuffer(CALC_PTR(float) in, int bufferSize, bool inverseFft)
    {
        return std::make_shared<CalculatorFftwFloat>(in,
                                                     std::make_shared<BufferTemplate<float>>(bufferSize),
                                                     createAccessStrategy<ACCESS_STRATEGY>(),
                                                     inverseFft);
    }
private:
    fftwf_plan m_fftwPlan = nullptr;
};

#endif // CALCULATORFFTFLOAT_H
