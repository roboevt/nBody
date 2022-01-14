#include <iostream>
#include "Engine.h"

int main()
{
    Engine engine;
    engine.init();
    engine.initParticles(0);
    engine.run();
}