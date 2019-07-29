#pragma once
namespace samples
{
    class Sample
    {
    public:
        Sample();
        virtual ~Sample();

        virtual void OnUpdate(float deltaTime);
        virtual void OnRender();
    };
}

