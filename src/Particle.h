#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vec2.h"
#include <cstdint>

struct Particle {
    int radius;

    Vec2 position;
    Vec2 velocity;

    float mass;
    float invMass;

    uint32_t color;

    Particle(float x, float y, float mass);
    ~Particle();

    void Move(float dt);
};

#endif
