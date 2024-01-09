#include "Application.h"
#include "Graphics.h"
#include "SDL2/SDL_keycode.h"
#include "Vec2.h"
#include <SDL2/SDL.h>
#include <memory>
#include <string>
#include "Particle.h"


bool Application::IsRunning() {
    return running;
}

void Application::Setup() {
    running = Graphics::OpenWindow();
}

void Application::Input() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    running = false;

            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT) {
                    int x,y;
                    SDL_GetMouseState(&x, &y);
                    std::shared_ptr<Particle> particle =std::make_shared<Particle>(x, y, 1.0);
                    particle->radius = 20;
                    particles.push_back(particle);
                }
                if (event.key.keysym.sym == SDLK_SPACE) {
                    for(int i = 0; i < 10; i++) {
                        auto particle = std::make_shared<Particle>(
                            static_cast<int>(Graphics::Width() / 2),
                            static_cast<int>(Graphics::Height() / 2),
                            1.0
                        );
                        particle->radius = 20;
                        particles.push_back(particle);
                    }
                }
                break;

        }
    }
}


void Application::Update() {
    static int timePreviousFrame;
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - timePreviousFrame);
    if (timeToWait > 0)
        SDL_Delay(timeToWait);

    float deltaTime = (SDL_GetTicks() - timePreviousFrame) / 1000.0f;
    if (deltaTime > 0.016)
        deltaTime = 0.016;

    timePreviousFrame = SDL_GetTicks();


    for (auto particle: particles) {
        particle->Move(deltaTime);
    }

    // check the bounderies of the window
    for (auto particle: particles) {
        if (particle->position.x - particle->radius <= 0) {
            particle->position.x = particle->radius;
            particle->velocity.x *= -0.9;
        } else if (particle->position.x + particle->radius >= Graphics::Width()) {
            particle->position.x = Graphics::Width() - particle->radius;
            particle->velocity.x *= -0.9;
        }

        if (particle->position.y - particle->radius <= 0) {
            particle->position.y = particle->radius;
            particle->velocity.y *= -0.9;
        } else if (particle->position.y + particle->radius >= Graphics::Height()) {
            particle->position.y = Graphics::Height() - particle->radius;
            particle->velocity.y *= -0.9;
        }
    }

}

void Application::Render() {
    Graphics::ClearScreen(0xFF056263);

    for (auto particle: particles) {
        Graphics::DrawFillCircle(particle->position.x, particle->position.y, particle->radius, particle->color);
    }

    std::string message = "Total particles: " + std::to_string(particles.size());

    Graphics::DrawMsg(40, 40, const_cast<char*>(message.c_str()));

    Graphics::RenderFrame();

}

void Application::Destroy() {
    Graphics::CloseWindow();
}
