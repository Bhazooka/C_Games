#ifndef OBJECT_H
#define OBJECT_H

class Object {
public:
    float x, y;
    float speed_x, speed_y;
    float gravity = 0.98f;
    bool isRolling = false;

    virtual void Update();
    virtual void ApplyInertia() {}
};

#endif
