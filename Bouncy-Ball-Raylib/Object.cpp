#include "Object.h"
#include <raylib.h>

void Object::Update() {
    CheckMouseEvents();

    if (isRolling) {
        ApplyInertia();
    }

    //Apply gravity and movement only if not dragging
    if (!dragging) {
        x += speed_x;
        speed_y += gravity;
        y += speed_y;
    }
}

void Object::CheckMouseEvents() {
    Vector2 currentMousePos = GetMousePosition();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointCircle(currentMousePos, {x, y}, 20)) { 
        dragging = true;
        speed_x = speed_y = 0;                  //Stop movement while dragging
        lastMousePos = currentMousePos;
    }

    //While dragging, update position and calculate speed
    if (dragging) {
        x = currentMousePos.x;
        y = currentMousePos.y;

        //Calculate velocity based on the difference in mouse position
        //THERE HAS TO BE A BETTER WAY TO DO THIS
        speed_x = (currentMousePos.x - lastMousePos.x);
        speed_y = (currentMousePos.y - lastMousePos.y);
        lastMousePos = currentMousePos;

        //Stop dragging when mouse is released
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            dragging = false;
            //Apply throw damping to smooth out release
            speed_x *= throwDamping;
            speed_y *= throwDamping;
        }
    }
}
