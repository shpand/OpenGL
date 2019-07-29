#include "MovingSquareAndCubeSample.h"
#include "utils/Asserter.h"

namespace samples
{
    MovingSquareAndCubeSample::MovingSquareAndCubeSample()
    {
    }


    MovingSquareAndCubeSample::~MovingSquareAndCubeSample()
    {
    }

    void MovingSquareAndCubeSample::OnUpdate(float deltaTime)
    {
    }

    void MovingSquareAndCubeSample::OnRender()
    {
        GLCall(glClearColor(0.2f, 1, 1, 1));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }
}
