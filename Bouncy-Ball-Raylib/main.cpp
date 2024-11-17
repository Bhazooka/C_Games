/* By Bhazooka */
#include <iostream>
#include <raylib.h>
#include "Ball.h"
#include "Box.h"

using namespace std;

Ball ball(720.0f, 512.0f, 7, -7, 20); //Update to make it so that objects can be added anywhere
Ball ball2(320.0f, 612.0f, 9, -3, 20); //Update to make it so that objects can be added anywhere

Box box(723.0f, 250.0F, 7, -7, 40, 40); //Place the ball object

int main() {
    cout << "Starting the game" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Bouncy Ball");
    // ToggleFullscreen();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ball.Update();
        ball2.Update();
        box.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        ball2.Draw();
        box.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}