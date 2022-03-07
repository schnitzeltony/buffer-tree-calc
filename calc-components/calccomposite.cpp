#include "calccomposite.h"

CalcComposite::CalcComposite(std::vector<Ptr> components) :
    m_components(components)
{
}

void CalcComposite::doCalc(int)
{
}

void CalcComposite::prepareNextCalc()
{
    for(auto component : m_components) {
        component->prepareNextCalc();
    }
}

bool CalcComposite::tryStartCalc(int sampleCount)
{
    bool atLeastOneStarted = false;
    for(auto input : m_components) {
        if(!input->isDone()) {
            if(input->tryStartCalc(sampleCount)) {
                atLeastOneStarted = true;
            }
        }
    }
    return atLeastOneStarted;
}

bool CalcComposite::isDone() const
{
    bool done = true;
    for(auto component : m_components) {
        done &= component->isDone();
        if(!done) {
            break;
        }
    }
    return done;
}
