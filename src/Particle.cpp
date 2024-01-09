#include "Particle.h"
#include "Vec2.h"
#include <iostream>
#include <random>

Particle::Particle(float x, float y, float mass) {
    std::random_device rd;
    std::default_random_engine eng(rd());

    float min_v_value = -500.0;
    float max_v_value = 500.0;

    int min_color = 0;
    int max_color = 255;

    std::uniform_real_distribution<float> distr_v(min_v_value, max_v_value);
    std::uniform_int_distribution<int> distr(min_color, max_color);
    int red = distr(eng);
    int green = distr(eng);
    int blue = distr(eng);
    int alpha = distr(eng);

    // Combine the color channels into a single uint32_t color value
    uint32_t color = (alpha << 24) | (red << 16) | (green << 8) | blue;

    float random_v_x = distr_v(eng);
    float random_v_y = distr_v(eng);

    this->position = Vec2(x, y);
    this->mass = mass;
    if (mass != 0.0) {
        this->invMass = 1.0 / mass;
    } else {
        this->invMass = 0.0;
    }

    this->color = color;
    this->velocity.x = random_v_x;
    this->velocity.y = random_v_y;

}

Particle::~Particle() {

}

void Particle::Move(float dt) {
    position += velocity * dt;

}
