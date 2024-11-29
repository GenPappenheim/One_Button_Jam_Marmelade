#include "raylib.h"




bool CheckCollisionRingPoint(Vector2 circleCenter, float circleRadius, Vector2 checkPoint)
{
    float result = ((checkPoint.x - circleCenter.x)*(checkPoint.x - circleCenter.x)) + ((checkPoint.y - circleCenter.y)*(checkPoint.y - circleCenter.y));
    if(result == (circleRadius*circleRadius)) {
        return true;
    }
    else {
        return false;
    }
}






int main(void)
{
    const int screenWidth = 800;
    const int screenHeigth = 450;

    struct ringSize {
        float innerRadius;
        float outerRadius;
    };

    InitWindow(screenWidth, screenHeigth, "Ich bin das erste Window!");
    
    Vector2 center = {GetScreenWidth()/2.0f, GetScreenHeight()/2.0f};

    Rectangle testBox = {100, (GetScreenHeight()/2.0f)-50.0f, 50, 50};
    Vector2 testBoxOrigin = {testBox.x, testBox.y};
    bool rectangle = true;

    struct ringSize Dome;
    Dome.innerRadius = 100;
    Dome.outerRadius = 110;

    SetTargetFPS(60);


    while (!WindowShouldClose())
    {

        if (IsKeyDown(KEY_SPACE) == true) {
            Dome.innerRadius ++;
            Dome.outerRadius ++;
        }
        else {
            Dome.innerRadius --;
            Dome.outerRadius --;
            if ((Dome.innerRadius <= 30) | (Dome.outerRadius <= 40)) {
                Dome.innerRadius = 30;
                Dome.outerRadius = 40;
            }
        }

        
        bool collisionOccured = CheckCollisionRingPoint(center, Dome.outerRadius, testBoxOrigin);



        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        //DrawText("Hello World!", 190, 200, 20, BLACK);
        DrawFPS(20, 20);
        if (collisionOccured == true) {
            rectangle = false;
        }

        if(rectangle) {
        DrawRectangleRec(testBox, PINK);
        }
        
        DrawRing(center, Dome.innerRadius, Dome.outerRadius, 180.0f, 360.0f, 0, BLACK);
        

        EndDrawing();

    }

    CloseWindow();

    return 0;

}