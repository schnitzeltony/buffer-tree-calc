#ifndef NULLCOMPONENT_H
#define NULLCOMPONENT_H

#include "buffers/buffertemplate.h"
#include "calc-composite/abstractcalculationcomponent.h"

template <class T>
class NullComponent : public AbstractCalculationComponent
{
public:
    NullComponent(BUFFER_PTR inputOutput);

};

#endif // NULLCOMPONENT_H
