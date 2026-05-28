#include "core/Engine.hpp"

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    Engine& engine = Engine::getInstance();

    if (!engine.init("Rick Dangerous 1 - SDL3 Clone", 800, 600)) {
        return -1;
    }

    while (engine.isRunning()) {
        engine.handleEvents();
        engine.update();
        engine.render();
    }

    engine.clean();
    return 0;
}