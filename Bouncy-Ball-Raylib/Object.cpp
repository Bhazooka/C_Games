#include "Object.h"

void Object::Update() {
    if (isRolling) {
        ApplyInertia();
    }

    x += speed_x;
    speed_y += gravity;
    y += speed_y;
}
