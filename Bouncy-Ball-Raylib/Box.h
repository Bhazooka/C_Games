#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include <raylib.h>
#include <cmath>

class Box : public Object {
public:
    float width, height;
    float rotation = 0.0f;
    float inertia = 0.9f;
    bool onFlatSide = true;

    Box(float x, float y, int speed_x, int speed_y, float width, float height);

    void Update() override;
    void Draw() const;

    //Collision
    void HandleCollision(Object& other) override;
    Rectangle GetBoundingArea() const override; 

private:
    void ApplyInertia() override;
    void FlipOnCollision();
};

#endif
