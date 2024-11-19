/* By Bhazooka */
#include <iostream>
#include <raylib.h>
#include "Ball.h"
#include "Box.h"

using namespace std;

// Initialize objects
Ball ball(720.0f, 512.0f, 7, -7, 20);
Ball ball2(320.0f, 612.0f, 9, -3, 20);
Box box(723.0f, 250.0f, 7, -7, 40, 40);

int main() {
    cout << "Starting the game" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Bouncy Ball");
    // ToggleFullscreen();  //UPDATE THIS LATER
    SetTargetFPS(60);

    //toggling bounding boxes: For Depugging
    bool showBoundingBoxes = false;

    while (!WindowShouldClose()) {
        //Toggle bounding box visualization with 'D' key
        if (IsKeyPressed(KEY_D)) showBoundingBoxes = !showBoundingBoxes;

        ball.Update();
        ball2.Update();
        box.Update();

        //Draw everything
        BeginDrawing();
        ClearBackground(BLACK);

        ball.Draw();
        ball2.Draw();
        box.Draw();

        //Draw bounding boxes if debugging is enabled
        if (showBoundingBoxes) {
            Rectangle ballBounds = ball.GetBoundingArea();
            DrawRectangleLines(ballBounds.x, ballBounds.y, ballBounds.width, ballBounds.height, RED);

            Rectangle ball2Bounds = ball2.GetBoundingArea();
            DrawRectangleLines(ball2Bounds.x, ball2Bounds.y, ball2Bounds.width, ball2Bounds.height, GREEN);

            Rectangle boxBounds = box.GetBoundingArea();
            DrawRectangleLines(boxBounds.x, boxBounds.y, boxBounds.width, boxBounds.height, BLUE);
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
