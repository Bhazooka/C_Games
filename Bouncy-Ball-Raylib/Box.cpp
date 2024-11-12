#include "Box.h"
#include <raylib.h>

Box::Box(float x, float y, float size) {
    this->x = x;
    this->y = y;
    this->size = size;
    this->speed_x = 0;
    this->speed_y = 0;
    this->gravity = 0.98f;
}

void Box::Update() {
    // Apply gravity only if box isn't dragged
    if (!dragging) {
        speed_y += gravity;
        y += speed_y;

        // Horizontal movement
        x += speed_x;

        // Check for collision with ground or screen edges
        CheckCollisionWithGround();
    }
}

void Box::Draw() const {
    DrawRectangle(static_cast<int>(x - size / 2), static_cast<int>(y - size / 2), size, size, WHITE);
}

void Box::CheckCollisionWithGround() {
    float screenHeight = static_cast<float>(GetScreenHeight());

    if (y + size / 2 >= screenHeight) {
        y = screenHeight - size / 2;
        speed_y = 0; 
        Topple();     
    }
}

void Box::Topple() {
    
    onSide = !onSide;

    
    if (onSide) {
        speed_x *= 0.9f;  
    } else {
        speed_x = (speed_x > 0) ? 5.0f : -5.0f;  
    }
}
