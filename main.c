#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeigth = 450;

    InitWindow(screenWidth, screenHeigth, "Ich bin das erste Window!");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        
        ClearBackground(RAYWHITE);

        DrawText("Hello World!", 190, 200, 20, BLACK);
        DrawFPS(20, 20);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}