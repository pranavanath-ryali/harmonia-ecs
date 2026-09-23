#include "raylib.h"

// Smoothstep ease-in-out function: f(t) = 3t^2 - 2t^3
float EaseInOutSmoothstep(float t) {
    return t * t * (3.0f - 2.0f * t);
}

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib - Ease In-Out Ball Interpolation");

    // Animation variables
    float startX = 100.0f;
    float endX = 700.0f;
    float currentX = startX;
    float centerY = screenHeight / 2.0f;
    float radius = 30.0f;

    float progress = 0.0f;      // Normalized time (0.0 to 1.0)
    float duration = 0.75f;      // Time in seconds to traverse the screen
    int direction = 1;          // 1 = moving right, -1 = moving left

    while (!WindowShouldClose()) {
        // --- Update ---
        float deltaTime = GetFrameTime();
        
        // Advance normalized progress
        progress += (deltaTime / duration) * direction;

        // Bounce back and forth at the ends
        if (progress >= 1.0f) {
            progress = 1.0f;
            direction = -1;
        } else if (progress <= 0.0f) {
            progress = 0.0f;
            direction = 1;
        }

        // Apply ease in-out easing curve
        float easedProgress = EaseInOutSmoothstep(progress);

        // Linear interpolation (lerp) using the eased factor
        currentX = startX + (endX - startX) * easedProgress;

        // --- Draw ---
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // Draw start and end track markers
            DrawLine(startX, centerY, endX, centerY, LIGHTGRAY);
            DrawCircle(startX, centerY, 5, GRAY);
            DrawCircle(endX, centerY, 5, GRAY);

            // Draw moving ball
            DrawCircle((int)currentX, (int)centerY, radius, MAROON);

            DrawText("Smoothstep Easing (Ease In-Out)", 10, 10, 20, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
