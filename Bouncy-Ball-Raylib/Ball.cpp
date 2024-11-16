#include "Ball.h"
#include <cmath>

Ball::Ball(float x, float y, int speed_x, int speed_y, int radius) {
    this->x = x;
    this->y = y;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->radius = radius;
    this->isRolling = true;
}

void Ball::Draw() const {
    DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
}

void Ball::Update() {
    Object::Update();

    if (y + radius >= GetScreenHeight() || y - radius <= 0) {
        speed_y = -speed_y * 0.9f;
        if (y + radius >= GetScreenHeight()) y = GetScreenHeight() - radius;
        if (y - radius <= 0) y = radius;
    }

    if (x + radius >= GetScreenWidth() || x - radius <= 0) {
        speed_x = -speed_x * 0.2f;
        if (x + radius >= GetScreenWidth()) x = GetScreenWidth() - radius;
        if (x - radius <= 0) x = radius;
    }
}

void Ball::ApplyInertia() {
    speed_x *= inertia;
    speed_y *= inertia;
    if (fabs(speed_x) < 0.01f) speed_x = 0;
    if (fabs(speed_y) < 0.01f) speed_y = 0;
}


// COLLISION HANDLING SECTION
Rectangle Ball::GetBoundingArea() const {
    /*
        x - radius and y - radius: These values represent top-left 
        corner of the bounding box. Since the circle is centered at (x, y) 
        with radius 'radius', moving radius units left and up from the center 
        provides the top-left position. that's the starting point from which
        the BoundingArea is created -- to the point where the area must end
        which is calculated with radius*2 horizontally and vertically.

        radius * 2 (width) and radius * 2 (height): width and height are 
        equal to diameter (twice the radius). ensures the entire 
        circular area fits within the bounding box.
    */ 
    return{x - radius, y - radius, radius * 2, radius * 2};
}

//
void Ball::HandleCollision(Object& other){
    // COMPLETE FUNCTION TO HANDLE COLLISION FOR BALLS
    
}


