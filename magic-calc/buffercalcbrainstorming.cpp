#include "buffercalcbrainstorming.h"


void MagicBufferCalc::prepare()
{
    for(auto inputBuffer : m_strategy->getInputBuffers()) {
        inputBuffer->getMyCalcStrategy()->prepare();
    }
    m_strategy->getOutputBuffer()->getMyCalcStrategy()->prepare();
}

bool MagicBufferCalc::calculate()
{

}

void MagicBufferCalc::cleanup()
{

}
