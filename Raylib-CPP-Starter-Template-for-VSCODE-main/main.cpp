#include <iostream>
#include <raylib.h>

using namespace std;

//ADD COLOUR LATER

int player_score = 0;
int cpu_score = 0; 

class Ball {
    public:
        float x, y;
        int speed_x, speed_y;               //speed in x and y axis
        int radius;

        void Draw() {
            DrawCircle(x, y, radius, WHITE);     //(x,y,radius,colour)
        }

        void Update() {
            // simulate movement by increasing value of the x & y position
            x += speed_x;
            y += speed_y;

            if(y + radius >= GetScreenHeight() || y - radius <= 0) 
            {
                speed_y *= -1;                  //reverse speed if ball hits edge of screen (go in opposite direction)
            }
            if(x + radius >= GetScreenWidth()){ //CPU wins
                cpu_score++;
                ResetBall();

            }  
            if (x - radius <= 0){
                player_score++;
                ResetBall();
            }
        }

        void ResetBall(){
            x = GetScreenWidth()/2;
            y = GetScreenHeight()/2;

            /* Randomise direction ball gets thrown when starting the game by multiplying 
               speedx & speedy by either -1(for left or down) or 1(for right and up) */
            int speed_choices[2] = {-1,1};
            speed_x * speed_choices[GetRandomValue(0,1)];           // Randomise speed of ball by value of 0 or 1
            speed_y * speed_choices[GetRandomValue(0,1)];
        }
};

class Paddle {
    protected: 
        void LimitMovement() {
            if(y <= 0){
                y = 0;                                              //restrict paddle from passing edge of y border
            }
            if(y + height >= GetScreenHeight()){
                y = GetScreenHeight() - height;
            }
        }

    public:
        float x, y;
        float width, height;
        int speed;

        void Draw() {
            DrawRectangle(x, y, width, height, WHITE);              //FIRST PADDLE (x,y,width,height,colour)
        }

        void Update() {
            if(IsKeyDown(KEY_UP)){
                y -= speed;
            }
            if(IsKeyDown(KEY_DOWN)){
                y += speed;
            }
            
            LimitMovement();
        }
};


class CpuPaddle: public Paddle                                  //inheritance
{                                 
    public: 
        void Update(int ball_y)
        {
            if(y + height/2 > ball_y){
                y -= speed;
            }
            if(y + height/2 <= ball_y){
                y += speed;
            }

            LimitMovement();
        }
};


//Create Objects
Ball ball;
Paddle player;
CpuPaddle cpu;


int main () {

    cout << "Starting the game" << endl;
    const int screen_width = 1280;
    const int screen_height = 800;

    InitWindow(screen_width, screen_height, "Pong");            //Function defined raylib.h
    SetTargetFPS(60);                                           //Game FPS

    //Ball attribute values
    ball.radius = 20;
    ball.y = screen_height/2;
    ball.x = screen_width/2;
    ball.speed_x = 7;
    ball.speed_y = 7;
    //Player attribute values
    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10; 
    player.y = screen_height/2 - player.height/2;
    player.speed = 6;
    //CPU attributes
    cpu.width = 25;
    cpu.height = 120;
    cpu.x = 10;
    cpu.y = screen_height/2 - cpu.height/2;
    cpu.speed = 6;



    //Game Loop
    while(WindowShouldClose() == false ) {                                          //WindowShouldClose checks if close window icon or "Esc" is pressed, then returns true
        //Drawing coordinate (x,y) = (0,0) starts at top most left corner.
        BeginDrawing();

        ball.Update();                                                              //before drawing the ball, loop must first update its position
        player.Update();
        cpu.Update(ball.y);

        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height} )){
            ball.speed_x *= -1;                                                     //Reverse ball speed
        }
        if(CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{cpu.x, cpu.y, cpu.width, cpu.height} )) {
            ball.speed_x *= -1;
        }

        ClearBackground(BLACK);                                                     //Clears the background, so everything redraws. To get rid of objects trace from prev frames
        DrawLine(screen_width/2, 0, screen_width/2, screen_height, WHITE);          //(startPosX, startPosY, endPosX, endPosY, color)
        ball.Draw();                                                                
        player.Draw();
        cpu.Draw();
        DrawText(TextFormat("%i", cpu_score), screen_width/4 - 20, 20, 80, WHITE);
        DrawText(TextFormat("%i", player_score), 3 * screen_width/4 - 20, 20, 80, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}