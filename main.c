#include "raylib.h"

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

    struct ringSize Dome;
    Dome.innerRadius = 200.0f;
    Dome.outerRadius = 210.0f;

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


        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        //DrawText("Hello World!", 190, 200, 20, BLACK);
        DrawFPS(20, 20);

        DrawRing(center, Dome.innerRadius, Dome.outerRadius, 180.0f, 360.0f, 0, BLACK);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}