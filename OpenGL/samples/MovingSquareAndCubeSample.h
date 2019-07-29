#pragma once
#include "Sample.h"

namespace samples
{
    class MovingSquareAndCubeSample : public Sample
    {
    public:
        MovingSquareAndCubeSample();
        ~MovingSquareAndCubeSample();
        void OnUpdate(float deltaTime) override;
        void OnRender() override;
    };    
}

