#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include <raylib.h>
#include <cmath>

class Box : public Object {
public:
    float width, height;
    float rotation = 0.0f;
    bool onFlatSide = true;

    Box(float x, float y, float width, float height);

    void Update() override;
    void Draw() const;
    void HandleCollision(Object& other) override;
    Rectangle GetBoundingArea() const override; 

private:
    void ApplyInertia() override;
    void FlipOnCollision();
};

#endif
