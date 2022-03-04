#ifndef BUFFERTEMPLATE_H
#define BUFFERTEMPLATE_H

#include "calc-components/abstractcalculationcomponent.h"

#include <memory>
#include <cstddef>
#include <vector>

#define BUFFER_PTR(T) std::shared_ptr<BufferTemplate<T>>

template <class T, class Allocator = std::allocator<T>>
class BufferTemplate
{
public:
    BufferTemplate(std::size_t size, const Allocator& alloc = Allocator()) :
        m_buffer(size, alloc)
    {
    };

private:
    std::vector<T, Allocator> m_buffer;
};


#define CALC_PTR(INTYPE, OUTTYPE) std::shared_ptr<TCalculator<INTYPE, OUTTYPE>>

template <class INTYPE, class OUTTYPE>
class TCalculator : public AbstractCalculationComponent
{
public:
    TCalculator(std::vector<CALC_PTR(INTYPE, OUTTYPE)> inputCalculators, BUFFER_PTR(OUTTYPE) outputBuffer, AbstractAccessStrategy::Ptr accessStrategy) :
        AbstractCalculationComponent(accessStrategy),
        m_inputCalculators(inputCalculators),
        m_outputBuffer(outputBuffer)
    {
    }
    virtual bool doCalc(int sampleCount) override;
    virtual void init() override;
    virtual void destroy() override;
protected:
    virtual void doInit() {}
    virtual void doDestroy() {}
    std::vector<CALC_PTR(INTYPE, OUTTYPE)> m_inputCalculators;
    BUFFER_PTR(OUTTYPE) m_outputBuffer;
};


#endif // BUFFERTEMPLATE_H
