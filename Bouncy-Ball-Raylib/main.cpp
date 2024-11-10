#include <iostream>
#include <raylib.h>

using namespace std;

class Object {
    public:
        float x, y;
        float speed_x, speed_y;
        float gravity = 0.98f;

        //Add gravity to vertical speed
        virtual void Update(){                                          //Virtual is a base class member function that can be redifined in derived classes
            x += speed_x;
            speed_y += gravity;                                         //Simulate effects of gravity
            y += speed_y; 
        }
};

class Ball : public Object{
    public: 
        int radius;

        Ball(float x, float y, int speed_x, int speed_y, int radius) {
            this ->x = x;
            this ->y = y;
            this ->speed_x = speed_x;
            this ->speed_y = speed_y;
            this ->radius = radius;
        }

        void Draw() const {
            DrawCircle(static_cast<int>(x), static_cast<int>(y), radius, WHITE);
        }

        void Update() override {
            Object::Update();                                           //Calling base class update to handle gravity 

            if(y + radius >= GetScreenHeight() || y - radius <= 0) {
                speed_y = -speed_y * 0.9f;                              //Bounce back with 90% of the speed
                //Below is for the bounce effect. the point y must reach the contact with ground before it can bounce (I THINK)
                if (y + radius >= GetScreenHeight()) y = GetScreenHeight() - radius;
                if (y - radius <= 0) y = radius;
            }

            if(x + radius >= GetScreenWidth() || x - radius <= 0 ){
                speed_x = -speed_x * 0.9f;
                if (x + radius >= GetScreenWidth()) x = GetScreenWidth() - radius;
                if (x - radius <= 0) x = radius;

            }
        }
};

//Create Objects
Ball ball(640.0f, 400.0f, 7, -7, 20);

int main () {
    cout << "Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Bouncy Ball");                         //Function defined raylib.h
    SetTargetFPS(60);                                                               //Game FPS

    //Ball attribute values
    ball.radius = 20;
    ball.y = screen_height/2;
    ball.x = screen_width/2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    //Game Loop
    while(WindowShouldClose() == false ) {                                          //WindowShouldClose checks if close window icon or "Esc" is pressed, then returns true
        //Drawing coordinate (x,y) = (0,0) starts at top most left corner.
        ball.Update();                                                              //before drawing the ball, loop must first update its position

        BeginDrawing();

        ClearBackground(BLACK);                                                     //Clears the background, so everything redraws. To get rid of objects trace from prev frames
        ball.Draw();                                                                

        EndDrawing();
    }

    CloseWindow();
    return 0;
}