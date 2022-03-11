#include "calculatorfftwinvfloat.h"

CalculatorFftwInvFloat::CalculatorFftwInvFloat(CALC_PTR(std::complex<float>) inFft,
                                               BUFFER_PTR(float) outReal,
                                               AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorFftwInv<float>(
        {inFft},
        outReal,
        [&](int sampleCount){doCalc(sampleCount);},
        accessStrategy)
{
    // we work with bare pointers -> check
    if(m_outputBuffer->size() < inFft->getOutputBuffer()->size()) {
        throw std::out_of_range("Outbuffer too small real->fft-complex");
    }
    // reinterpret_cast allowed - see https://www.fftw.org/fftw3_doc/Complex-numbers.html
    m_fftwPlan = fftwf_plan_dft_c2r_1d(m_outputBuffer->size(),
                                       reinterpret_cast<fftwf_complex*>(inFft->getOutputBuffer()->data()),
                                       m_outputBuffer->data(),
                                       FFTW_ESTIMATE);
}

CalculatorFftwInvFloat::~CalculatorFftwInvFloat()
{
    fftwf_destroy_plan(m_fftwPlan);
}

void CalculatorFftwInvFloat::doCalc(int)
{
    fftwf_execute(m_fftwPlan);
}
