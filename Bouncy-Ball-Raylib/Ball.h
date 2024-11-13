#ifndef BALL_H
#define BALL_H

#include "Object.h"
#include <raylib.h>

class Ball : public Object {
public:
    int radius;
    bool isRolling;
    float inertia = 0.2f;

    Ball(float x, float y, int speed_x, int speed_y, int radius);
    
    void Draw() const;
    void Update() override;
    void ApplyInertia() override;

    //Collision Handling
    void HandleCollision(Object& other) override;
    Rectangle GetBoundingArea() const override;
};

#endif
