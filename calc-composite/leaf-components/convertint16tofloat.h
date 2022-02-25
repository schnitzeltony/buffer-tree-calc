#ifndef CONVERTINT16TOFLOAT_H
#define CONVERTINT16TOFLOAT_H

#include "calc-composite/abstractcalculationcomponent.h"
#include "buffers/buffervectorint16.h"
#include "buffers/bufferbarefloat.h"

class ConvertInt16ToBareFloat : public AbstractCalculationComponent
{
public:
    ConvertInt16ToBareFloat(AbstractAccessStrategy::Ptr accessStrategy,
                            BufferVectorInt16Ptr input,
                            BufferBareFloat::Ptr output);
    virtual bool doCalc(int subBufferNo) override;
private:
    BufferVectorInt16Ptr m_input;
    BufferBareFloat::Ptr m_output;
};

#endif // CONVERTINT16TOFLOAT_H
