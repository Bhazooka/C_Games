/* By Bhazooka */
#include <iostream>
#include <raylib.h>
#include "Ball.h"

using namespace std;

Ball ball(720.0f, 512.0f, 7, -7, 20);

int main() {
    cout << "Starting the game" << endl;

    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Bouncy Ball");
    // ToggleFullscreen();
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ball.Update();

        BeginDrawing();
        ClearBackground(BLACK);
        ball.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}