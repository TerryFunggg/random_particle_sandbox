#ifndef APPLICATION_H
#define APPLICATION_H

#include "./Graphics.h"
#include "./Particle.h"
#include "./Vec2.h"
#include "SDL2/SDL_rect.h"
#include <vector>

const int FPS = 60;
const int MILLISECS_PER_FRAME = 1000 / FPS;

const int PIXELS_PER_METER = 50;

class Application {
    private:
        bool running = false;

        std::vector<Particle*> particles;

    public:
        Application() = default;
        ~Application() = default;
        bool IsRunning();
        void Setup();
        void Input();
        void Update();
        void Render();
        void Destroy();
};

#endif
