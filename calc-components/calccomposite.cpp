#include "calccomposite.h"

CalcComposite::CalcComposite(std::vector<Ptr> components) :
    m_components(components)
{
}

void CalcComposite::doCalc(int)
{
}

void CalcComposite::init()
{
    for(auto component : m_components) {
        component->init();
    }
}

void CalcComposite::destroy()
{
    for(auto component : m_components) {
        component->destroy();
    }
}

void CalcComposite::prepareCalc()
{
    for(auto component : m_components) {
        component->prepareCalc();
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
