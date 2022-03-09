#include "calculatorfftwfloat.h"
#include <stdexcept>

CalculatorFftwFloat::CalculatorFftwFloat(CALC_PTR(float) inReal,
                                         BUFFER_PTR(std::complex<float>) outFft,
                                         AbstractAccessStrategy::Ptr accessStrategy) :
    CalculatorFftw<float>(inReal, outFft, accessStrategy)
{
    // we work with bare pointers -> check
    if(m_outputBuffer->size() < inReal->getOutputBuffer()->size()) {
        throw std::out_of_range("Outbuffer too small real->fft-complex");
    }
    // reinterpret_cast allowed - see https://www.fftw.org/fftw3_doc/Complex-numbers.html
    m_fftwPlan = fftwf_plan_dft_r2c_1d(m_outputBuffer->size(),
                                       inReal->getOutputBuffer()->data(),
                                       reinterpret_cast<fftwf_complex*>(m_outputBuffer->data()),
                                       FFTW_ESTIMATE);
}

CalculatorFftwFloat::~CalculatorFftwFloat()
{
    fftwf_destroy_plan(m_fftwPlan);
}

void CalculatorFftwFloat::doCalc(int)
{
    fftwf_execute(m_fftwPlan);
}
