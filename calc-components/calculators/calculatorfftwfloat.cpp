#include "calculatorfftwfloat.h"
#include <stdexcept>

CalculatorFftwFloat::CalculatorFftwFloat(CALC_PTR(float) in,
                                         BUFFER_PTR(float) out,
                                         AbstractAccessStrategy::Ptr accessStrategy,
                                         bool inverseFft) :
    CalculatorFftw<float>({in}, out, accessStrategy, inverseFft)
{
    if(!inverseFft) {
        // we work with bare pointers -> check (factor two for complex)
        if(out->size() < m_inBuffer->size()*2) {
            throw std::out_of_range("Outbuffer too small real->fft-complex");
        }
        m_fftwPlan = fftwf_plan_dft_r2c_1d(m_inBuffer->size(),
                                           m_inBuffer->data(),
                                           reinterpret_cast<fftwf_complex*>(out->data()),
                                           FFTW_ESTIMATE);
    }
    else {
        if(out->size()*2 < m_inBuffer->size()) {
            throw std::out_of_range("Outbuffer too small real->fft-complex");
        }
        m_fftwPlan = fftwf_plan_dft_c2r_1d(m_inBuffer->size(),
                                           reinterpret_cast<fftwf_complex*>(m_inBuffer->data()),
                                           out->data(),
                                           FFTW_ESTIMATE);
    }
}

CalculatorFftwFloat::~CalculatorFftwFloat()
{
    fftwf_destroy_plan(m_fftwPlan);
}

void CalculatorFftwFloat::doCalc(int)
{
    fftwf_execute(m_fftwPlan);
}
