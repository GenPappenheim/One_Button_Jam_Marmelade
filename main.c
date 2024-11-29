#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "raylib.h"

#define STEPS 256

typedef struct {
        float innerRadius;
        float outerRadius;
    } ringSize;

bool checkCollision = false;

void CheckCollisionEnemy(Vector2 *points, Rectangle enemy){
    for (int i = 0; i < STEPS; i++) {
        if (CheckCollisionPointRec(points[i], enemy)) {
            checkCollision = true;
        } else {
            checkCollision = false;
        }
    }
}


bool CheckCollisionRingPoint(Vector2 circleCenter, ringSize circleRadius, Vector2 checkPoint)
{
    float result = ((checkPoint.x - circleCenter.x)*(checkPoint.x - circleCenter.x)) + ((checkPoint.y - circleCenter.y)*(checkPoint.y - circleCenter.y));
    if((result >= (circleRadius.innerRadius*circleRadius.outerRadius)) && (result <= (circleRadius.outerRadius*circleRadius.outerRadius))) {
        return true;
    }
    else {
        return false;
    }
}

void CheckInput(ringSize *Dome, int screenWidth) {
    if (IsKeyDown(KEY_SPACE) == true && (Dome->innerRadius <= screenWidth/2)) {
            Dome->innerRadius ++;
            Dome->outerRadius ++;
        }
        else {
            Dome->innerRadius --;
            Dome->outerRadius --;
            if ((Dome->innerRadius <= 30) || (Dome->outerRadius <= 40)) {
                Dome->innerRadius = 30;
                Dome->outerRadius = 40;
            }
        }
}

void CalculateDome(float centerX, float centerY, float radius, Vector2* points) {
    float angleStep = PI / STEPS;
    for (int i = 0; i <= STEPS; i++) {
        float angle = -i * angleStep;
        points[i].x = centerX + radius * cos(angle);
        points[i].y = centerY + radius * sin(angle);
    }
}

void DrawHalfCircle(Vector2* points) {
    for (int i = 0; i < STEPS; i++) {
        Color colors[] = {LIGHTGRAY, GRAY, DARKGRAY, RED};
        Vector2 size = (Vector2) {5, 5};
        DrawRectangleV(points[i], size, colors[rand()%4]);
    }   
}


int main(void)
{
    const int screenWidth = 800;
    const int screenHeigth = 450;
    Vector2 points[STEPS] = {0};

    InitWindow(screenWidth, screenHeigth, "Ich bin das erste Window!");
    Vector2 center = {GetScreenWidth()/2.0f, GetScreenHeight() - 50};

    Rectangle enemy = {100, (GetScreenHeight() -50)-50.0f, 50, 50};
    Vector2 testBoxOrigin = {enemy.x, enemy.y};
    bool rectangle = true;

    ringSize *Dome = (ringSize *)malloc(sizeof(ringSize));
    if (Dome == NULL) {
        printf("Memory allocation failed :(");
        return -1;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()){

        CheckInput(Dome, screenWidth);  

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawFPS(20, 20);

        const char *collision = checkCollision ? "true" : "false";
        DrawText(collision, 20, 40, 20, GREEN);
        DrawRectangle(0, screenHeigth - 50, screenWidth, 50, GREEN);
        DrawRectangleRec(enemy, PINK);

        CalculateDome(center.x, center.y, Dome->innerRadius, points);
        CheckCollisionEnemy(points, enemy);
        DrawHalfCircle(points);

        EndDrawing();

    }

    CloseWindow();

    return 0;

}