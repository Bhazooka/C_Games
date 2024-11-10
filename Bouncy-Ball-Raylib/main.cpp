/* By Bhazooka */

#include <iostream>
#include <raylib.h>
#include <cmath>

using namespace std;

class Object {
    public:
        float x, y;
        float speed_x, speed_y;
        float gravity = 0.98f;
        bool isRolling = false;                                                     //For cicular objects

        //Add gravity to vertical speed
        virtual void Update(){                                                      //Virtual is a base class member function that can be redifined in derived classes
            if(isRolling) {
                ApplyInertia();
            }

            x += speed_x;
            speed_y += gravity;                                                     //Simulate effects of gravity
            y += speed_y; 
        }

        //This function should only be implemented for circular object
        virtual void ApplyInertia() {}
};

class Ball : public Object{
    public: 
        int radius;
        bool isRolling = false;
        float inertia = 0.7f;                                                      //Damping factor to gradually reduce speed

        Ball(float x, float y, int speed_x, int speed_y, int radius) {
            this -> x = x;
            this -> y = y;
            this -> speed_x = speed_x;
            this -> speed_y = speed_y;
            this -> radius = radius;
            this -> isRolling = true;                                               //Set ball to roll 
        }

        void Draw() const {
            DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
        }

        void Update() override {
            Object::Update();                                                       //Calling base class update to handle gravity 
            
            if(y + radius >= GetScreenHeight() || y - radius <= 0) {            
                speed_y = -speed_y * 0.9f;                                          //Bounce back with 90% of the speed
                // To ensure ball doesnt get stuck and go through the edges
                if (y + radius >= GetScreenHeight()) y = GetScreenHeight() - radius;
                if (y - radius <= 0) y = radius;
            }
            if(x + radius >= GetScreenWidth() || x - radius <= 0 ){
                speed_x = -speed_x * 0.9f;
                if (x + radius >= GetScreenWidth()) x = GetScreenWidth() - radius;
                if (x - radius <= 0) x = radius;
            }
        }

        void ApplyInertia() override {
            speed_x *= inertia;
            speed_y *= inertia;
            // If speed stops below a threshhold 0.01f, speed is set to 0
            if(fabs(speed_x) < 0.01f) speed_x = 0;                                  //fabs (cmath lib) returns the floating absolute value of a number
            if(fabs(speed_y) < 0.01f) speed_y = 0;
        }
};

//Create Objects
Ball ball(720.0f, 512.0f, 7, -7, 20);

int main () {
    cout << "Starting the game" << endl;
    
    const int screen_width = 1280;       // Initial width
    const int screen_height = 720;       // Initial height

    InitWindow(screen_width, screen_height, "Bouncy Ball");
    ToggleFullscreen();                  // Enable full screen mode
    SetTargetFPS(60);

    // Game Loop
    while (!WindowShouldClose()) {       // WindowShouldClose checks if close window icon or "Esc" is pressed, then returns true
        ball.Update();                   // Update ball position

        BeginDrawing();
        ClearBackground(BLACK);          // Clear background for clean redraw
        ball.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}