#ifndef OBJECT_H
#define OBJECT_H

#include <raylib.h>

class Object {
public:
    float x, y;
    float speed_x = 0.0f, speed_y = 0.0f;
    float gravity = 0.98f;
    bool isRolling = false;
    bool dragging = false;

    Vector2 lastMousePos = {0.0f, 0.0f};    //Track last mouse position
    float throwDamping = 0.09f;             //Damping factor for throw speed decay

    virtual void Update();
    virtual void ApplyInertia() { }
    void CheckMouseEvents();
};

#endif
