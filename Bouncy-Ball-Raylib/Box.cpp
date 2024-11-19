#include "Box.h"
#include <cmath>
#include "raymath.h"
#include "Ball.h"

Box::Box(float x, float y, int speed_x, int speed_y, float width, float height) {
    this->x = x;
    this->y = y;
    this->speed_x = speed_x;
    this->speed_y = speed_y;
    this->width = width;
    this->height = height;
    // onFlatSide = true;
    isRolling = false;
};

void Box::Draw() const {
    // Vector2 origin = { width/0.2f, height/0.2f };
    // // DrawRectangle(static_cast<int>(x), static_cast<int>(y), width, height, WHITE);
    // DrawRectanglePro({x, y, width, height}, origin, rotation, WHITE);

    Vector2 origin = { 0.0f , 0.0f };         //center of rectangle
    Rectangle rect = { x, y, width, height };
    DrawRectanglePro(rect, origin, 0.5f, WHITE);
}

void Box::Update() {
    Object::Update();

    if (!onFlatSide) {
        ApplyInertia();
    }

    //boundary conditions to ensure proper collision with edges
    if (y + height >= GetScreenHeight()) {
        speed_y = -speed_y * 0.1f;
        y = GetScreenHeight() - height; //touch and stop at bottom edge
    } else if (y <= 0) {
        speed_y = -speed_y * 0.1f;
        y = 0; // Adjust position to touch top edge
    }

    if (x + width >= GetScreenWidth()) {
        speed_x = -speed_x * 0.1f;
        x = GetScreenWidth() - width; // Adjust position to touch right edge
    } else if (x <= 0) {
        speed_x = -speed_x * 0.1f;
        x = 0; // Adjust position to touch left edge
    }
}



//REVIEW THIS METHOD
void Box::ApplyInertia() {
    speed_x *= inertia;
    speed_y *= inertia;

    //Stop rotation if movement slows down enough
    if(fabs(speed_x) < 0.1f && fabs(speed_y) < 0.1f) {
        speed_x = speed_y = 0;
        onFlatSide = true;
    }
}

void Box::FlipOnCollision() {
    if(onFlatSide) {
        rotation += 90.0f;      //MAKE IT SO THAT THIS IS VARIABLE BASED ON THE FORCE APPLIED TO A CERTAIN CORNER OF THE SQUARE
        onFlatSide = false;
    }
}


void Box::HandleCollision(Object& other) {
    Rectangle thisBounding = GetBoundingArea();
    Rectangle otherBounding = other.GetBoundingArea();

    if (!CheckCollisionRecs(thisBounding, otherBounding)) {
        return;
    }

    float deltaX = x - other.x;
    float deltaY = y - other.y;

    if (auto* otherBox = dynamic_cast<Box*>(&other)) {
        // Box-to-Box collision
        float overlapX = (width / 2 + otherBox->width / 2) - fabs(deltaX);
        float overlapY = (height / 2 + otherBox->height / 2) - fabs(deltaY);

        if (overlapX < overlapY) {
            // Resolve x-axis collision
            if (deltaX > 0) {
                x += overlapX * 0.5f;
                other.x -= overlapX * 0.5f;
            } else {
                x -= overlapX * 0.5f;
                other.x += overlapX * 0.5f;
            }
            speed_x = -speed_x * 0.9f;
            other.speed_x = -other.speed_x * 0.9f;
        } else {
            // Resolve y-axis collision
            if (deltaY > 0) {
                y += overlapY * 0.5f;
                other.y -= overlapY * 0.5f;
            } else {
                y -= overlapY * 0.5f;
                other.y += overlapY * 0.5f;
            }
            speed_y = -speed_y * 0.9f;
            other.speed_y = -other.speed_y * 0.9f;
        }
    } else if (auto* otherBall = dynamic_cast<Ball*>(&other)) {
        // If `other` is a Ball, `otherBall` is a pointer to it.
        // Handle ball-to-ball collision logic here.
        // Box-to-Ball collision
        float overlapX = (width / 2 + otherBall->radius) - fabs(deltaX);
        float overlapY = (height / 2 + otherBall->radius) - fabs(deltaY);

        if (overlapX < overlapY) {
            if (deltaX > 0) {
                otherBall->x += overlapX;
            } else {
                otherBall->x -= overlapX;
            }
            otherBall->speed_x = -otherBall->speed_x * 0.9f;
        } else {
            if (deltaY > 0) {
                otherBall->y += overlapY;
            } else {
                otherBall->y -= overlapY;
            }
            otherBall->speed_y = -otherBall->speed_y * 0.9f;
        }
    }
}



Rectangle Box::GetBoundingArea() const{
    /* 
        Returns an axis-aligned bounding box (AABB) centered on the box's position.
        The bounding box is used in broad-phase collision detection to identify potential 
        overlaps with other objects. The returned Rectangle defines the area extending 
        from the calculated top-left corner (x - width/2, y - height/2) to the specified 
        width and height.

        - (x - width/2, y - height/2): calculates the top-left corner of the box's bounding area.
        - width and height: specify the dimensions of the rectangle, 
        extending equally from the box's center (x, y) on all sides.
    */
    return {x - width/2, y - height/2, width, height};
}