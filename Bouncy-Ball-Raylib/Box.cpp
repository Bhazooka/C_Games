#include "Box.h"
#include <cmath>
#include "raymath.h"

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

    Vector2 origin = { width/2, height/2 };         //center of rectangle
    // Draw rectangle with proper center alignment and rotation
    Rectangle rect = { x - width/2, y - height/2, width, height };
    DrawRectanglePro(rect, origin, rotation, WHITE);
}

void Box::Update() {
    Object::Update();      

    if(!onFlatSide){
        ApplyInertia();
    }

    if (y + height >= GetScreenHeight() || y - height <= 0) {
        speed_y = -speed_y * 0.1f;
        if(y + height >= GetScreenHeight()) y = GetScreenHeight() - height;
        if(y - height <= 0) y = height;
    }

    if (x + width >= GetScreenWidth() || x - width <= 0) {
        speed_x = -speed_x * 0.1f;
        if(x + width >= GetScreenWidth()) x = GetScreenWidth() - width;
        if(x - width <= 0) x = width;
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
    // COMPLETE FUNCTION TO HANDLE COLLISION FOR SQUARES

    //Get the bounding area for both objects
    Rectangle otherBounding = other.GetBoundingArea();
    Rectangle thisBounding = GetBoundingArea();
    // Check for overlap between bounding rectangles
    if (CheckCollisionRecs(thisBounding, otherBounding)) {
        //Simple response: invert velocity in both x and 
        speed_x = -speed_x * 0.8f;
        speed_y = -speed_y * 0.8f;
        //Adjust position to avoid overlap
        if (other.y > y) y -= height/2;

        FlipOnCollision();
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