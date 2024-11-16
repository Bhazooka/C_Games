#include "Object.h"
#include <raylib.h>
#include <cmath>

void Object::Update() {
    CheckMouseEvents();
        
    if (isRolling) {
        ApplyInertia();
    }

    //Apply gravity and movement only if not dragging
    if (!dragging) {
        speed_y += gravity;
        x += speed_x;
        y += speed_y;
    }
}

void Object::CheckMouseEvents() {
    Vector2 currentMousePos = GetMousePosition();

    // Check if the mouse is clicking within the bounding area
    Rectangle boundingArea = GetBoundingArea();
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
        CheckCollisionPointRec(currentMousePos, boundingArea)) {
        dragging = true;
        speed_x = speed_y = 0; // Stop movement while dragging
        lastMousePos = currentMousePos;
    }

    // While dragging, update position and calculate speed
    if (dragging) {
        x = currentMousePos.x - boundingArea.width / 2; // Align box center to mouse
        y = currentMousePos.y - boundingArea.height / 2;

        // Calculate velocity based on the difference in mouse position
        speed_x = currentMousePos.x - lastMousePos.x;
        speed_y = currentMousePos.y - lastMousePos.y;
        lastMousePos = currentMousePos;

        // Stop dragging when mouse is released
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
            dragging = false;
            // Apply throw damping to smooth out release
            speed_x *= throwDamping;
            speed_y *= throwDamping;
        }
    }
}


//Collision with other objects
void Object::CheckCollisionWith(Object& other){
    //If the bounding areas intersect, deligate specific-shapes to handle collision
    if(CheckCollisionRecs(GetBoundingArea(), other.GetBoundingArea())){ 
        /*  
            Call HandleCollision on the current object (this) to let it
            handle its response to colliding with other object.
            Each object can define its own specific collision response,
            allowing different shapes (like circles & squares) to handle
            collisions uniquely. 
        */
        this->HandleCollision(other);
        /*  
            Call HandleCollision on 'other' object to allow it 
            to respond to colliding with the current object (this).
            This enables both objects to adjust their position, speed, 
            and behavior based on the collision interaction.
        */
        other.HandleCollision(*this);

    }
};
