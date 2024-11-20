// /* By Bhazooka */
// #include <iostream>
// #include <raylib.h>
// #include "Ball.h"
// #include "Box.h"
// #include <vector>

// using namespace std;

// const int screen_width = 1280;
// const int screen_height = 800;

// float GenerateRandomFloat(float min, float max) {
//     return min + static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f * (max - min);
// }

// //Check if BoundingAreas rectangles overlap
// bool CheckOverlap(Rectangle rect1, Rectangle rect2) {
//     return CheckCollisionRecs(rect1, rect2);
// }

// //Generate a random position that doesn't overlap with existing objects
// Vector2 GenerateRandomPosition(const vector<Object*>& objects, float width, float height) {
//     Rectangle newRect;
//     Vector2 position;

//     do {
//         //Generate random position within screen bounds
//         position.x = GenerateRandomFloat(width / 2, screen_width - width / 2);
//         position.y = GenerateRandomFloat(height / 2, screen_height - height / 2);
//         newRect = {position.x - width / 2, position.y - height / 2, width, height};

//         //Check for overlap with all existing objects
//         bool overlaps = false;
//         for (auto obj : objects) {
//             if (CheckOverlap(newRect, obj->GetBoundingArea())) {
//                 overlaps = true;
//                 break;
//             }
//         }

//         if (!overlaps) break;

//     } while (true);

//     return position;
// }

// int main() {
//     cout << "Starting the game" << endl;

//     InitWindow(screen_width, screen_height, "Bouncy Ball");
//     SetTargetFPS(60);

//     //Objects vector for collision checks
//     vector<Object*> objects;

//     //TODO: MAKE IT SO THAT WE CAN ADD OBJECTS AT WILL
//     //TEST OBJECTS
//     //Initialize objects with random positions and speeds
//     //CIRCLE
//     Vector2 pos1 = GenerateRandomPosition(objects, 40, 40);
//     Ball ball(pos1.x, pos1.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 20);
//     objects.push_back(&ball);
//     //CIRCLE
//     Vector2 pos2 = GenerateRandomPosition(objects, 40, 40);
//     Ball ball2(pos2.x, pos2.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 20);
//     objects.push_back(&ball2);
//     //SQUARE
//     Vector2 pos3 = GenerateRandomPosition(objects, 40, 40);
//     Box box(pos3.x, pos3.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 40, 40);
//     objects.push_back(&box);

//     //Bounding boxes: For Debugging
//     bool showBoundingBoxes = false;

//     while (!WindowShouldClose()) {
//         //Toggle bounding box with 'D'
//         if (IsKeyPressed(KEY_D)) {
//             showBoundingBoxes = !showBoundingBoxes;
//         }

//         ball.Update();
//         ball2.Update();
//         box.Update();

//         //Draw everything
//         BeginDrawing();
//         ClearBackground(BLACK);

//         ball.Draw();
//         ball2.Draw();
//         box.Draw();

//         //Draw bounding boxes if debugging is enabled
//         if (showBoundingBoxes) {
//             for (auto obj : objects) {
//                 Rectangle bounds = obj->GetBoundingArea();
//                 DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, RED);
//             }
//         }

//         EndDrawing();
//     }

//     CloseWindow();
//     return 0;
// }



// /*

//     TODO:
//     - Object Collision
//     - Upon collision, objects react according to laws of physics
//         - Add force (direction of the force applied)
//         - Add weight to objects for more accurate collisions
//     - Toggle gravity on and off (PRESS G)
//     - Press Button to make mouse cursor a repelant
//     - Select Object and it Create in real time

// */


/* By Bhazooka */
#include <iostream>
#include <raylib.h>
#include "Ball.h"
#include "Box.h"
#include <vector>

using namespace std;

const int screen_width = 1280;
const int screen_height = 800;

float GenerateRandomFloat(float min, float max) {
    return min + static_cast<float>(GetRandomValue(0, 10000)) / 10000.0f * (max - min);
}

//Check if BoundingAreas rectangles overlap
bool CheckOverlap(Rectangle rect1, Rectangle rect2) {
    return CheckCollisionRecs(rect1, rect2);
}

//Generate a random position that doesn't overlap with existing objects
Vector2 GenerateRandomPosition(const vector<Object*>& objects, float width, float height) {
    Rectangle newRect;
    Vector2 position;

    do {
        //Generate random position within screen bounds
        position.x = GenerateRandomFloat(width / 2, screen_width - width / 2);
        position.y = GenerateRandomFloat(height / 2, screen_height - height / 2);
        newRect = {position.x - width / 2, position.y - height / 2, width, height};

        //Check for overlap with all existing objects
        bool overlaps = false;
        for (auto obj : objects) {
            if (CheckOverlap(newRect, obj->GetBoundingArea())) {
                overlaps = true;
                break;
            }
        }

        if (!overlaps) break;

    } while (true);

    return position;
}

//GENERAL collision handling between two objects
void HandleCollision(Object& obj1, Object& obj2) {
    Rectangle rect1 = obj1.GetBoundingArea();
    Rectangle rect2 = obj2.GetBoundingArea();

    if (CheckOverlap(rect1, rect2)) {
        // Reverse directions (simplified response)
        obj1.speed_x *= -1;
        obj1.speed_y *= -1;
        obj2.speed_x *= -1;
        obj2.speed_y *= -1;

        // Slightly separate objects to avoid overlap sticking
        float overlapX = (rect1.x + rect1.width / 2) - (rect2.x + rect2.width / 2);
        float overlapY = (rect1.y + rect1.height / 2) - (rect2.y + rect2.height / 2);

        if (fabs(overlapX) > fabs(overlapY)) {
            obj1.x += overlapX > 0 ? 5.0f : -5.0f;
            obj2.x += overlapX > 0 ? -5.0f : 5.0f;
        } else {
            obj1.y += overlapY > 0 ? 5.0f : -5.0f;
            obj2.y += overlapY > 0 ? -5.0f : 5.0f;
        }
    }
}

int main() {
    cout << "Starting the game" << endl;

    InitWindow(screen_width, screen_height, "Bouncy Ball");
    SetTargetFPS(60);

    //Objects vector for collision checks
    vector<Object*> objects;

    //TODO: MAKE IT SO THAT WE CAN ADD OBJECTS AT WILL
    //TEST OBJECTS
    //Initialize objects with random positions and speeds
    //CIRCLE
    Vector2 pos1 = GenerateRandomPosition(objects, 40, 40);
    Ball ball(pos1.x, pos1.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 20);
    objects.push_back(&ball);
    //CIRCLE
    Vector2 pos2 = GenerateRandomPosition(objects, 40, 40);
    Ball ball2(pos2.x, pos2.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 20);
    objects.push_back(&ball2);
    //SQUARE
    Vector2 pos3 = GenerateRandomPosition(objects, 40, 40);
    Box box(pos3.x, pos3.y, GenerateRandomFloat(-10, 10), GenerateRandomFloat(-10, 10), 40, 40);
    objects.push_back(&box);

    //Bounding boxes: For Debugging
    bool showBoundingBoxes = false;

    while (!WindowShouldClose()) {
        //Toggle bounding box with 'D'
        if (IsKeyPressed(KEY_D)) {
            showBoundingBoxes = !showBoundingBoxes;
        }

        //Update all objects
        for (auto obj : objects) {
            obj->Update();
        }

        //Collision handling between all objects
        for (size_t i = 0; i < objects.size(); i++) {
            for (size_t j = i + 1; j < objects.size(); j++) {
                HandleCollision(*objects[i], *objects[j]);
            }
        }

        //Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        for (auto obj : objects) {
            obj->Draw();
        }

        //Draw bounding boxes if debugging is enabled
        if (showBoundingBoxes) {
            for (auto obj : objects) {
                Rectangle bounds = obj->GetBoundingArea();
                DrawRectangleLines(bounds.x, bounds.y, bounds.width, bounds.height, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}

/*
    TODO:
    - Object Collision
    - Upon collision, objects react according to laws of physics
        - Add force (direction of the force applied)
        - Add weight to objects for more accurate collisions
    - Toggle gravity on and off (PRESS G)
    - Press Button to make mouse cursor a repelant
    - Select Object and it Create in real time

*/
