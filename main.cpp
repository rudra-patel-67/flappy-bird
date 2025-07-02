#if defined(PLATFORM_WEB)
#include <emscripten/emscripten.h>
#endif
#include "global.cpp"


int main(){
    
    // .................................................................
    // Initialization
    // .................................................................
    windowTitle = "Flappy Bird";
    birdBoundingCircle = {windowWidth/4.0f,(windowHeight/2.0f)-10.0f,30.0f};
    
    
    // SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(720,1080,windowTitle.c_str());
    // SetExitKey(KEY_NULL);

    #if defined(PLATFORM_WEB)
        emscripten_set_main_loop(UpdateDrawFrame, 0, 1);
    #else
        SetTargetFPS(fps);   // Set our game to run at 60 frames-per-second
        //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame();
        deltaTime++;
    }

    #endif

    CloseWindow();
    return 0;
}

void UpdateDrawFrame(void)
{
    //----------------------------------------------------------------------------------
    // Update
    //----------------------------------------------------------------------------------

    if(birdBoundingCircle.y+30<windowHeight && birdBoundingCircle.y-30>0)
    {
        birdBoundingCircle.y+=birdVelocity;
        std::cout<<birdVelocity<<std::endl;
        // std::cout<<birdBoundingCircle.x<<"\t"<<birdBoundingCircle.y<<"\t"<<birdBoundingCircle.z<<"\t"<<windowWidth<<"\t"<<windowHeight<<std::endl;
    }

    if(IsKeyPressed(KEY_SPACE)){
            birdJump();
    }
    if(IsKeyDown(KEY_R)){
        birdBoundingCircle.y=(windowHeight/2.0f)-10.0f;
    }


    // "Are you sure you want to exit (Not for web)"
    // if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;    
    // if (exitWindowRequested)
    // {
    //     // A request for close window has been issued, we can save data before closing
    //     // or just show a message asking for confirmation
    //     if (IsKeyPressed(KEY_Y)) exitWindow = true;
    //     else if (IsKeyPressed(KEY_N)) exitWindowRequested = false;
    // }

    //----------------------------------------------------------------------------------
    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

    ClearBackground(SKYBLUE);
    
    DrawRectangleLines(0,0,windowWidth,windowHeight,BLACK);

    if (GameOver)
    {
        DrawText("Game Over", 60, windowHeight/2-40, 30, BLACK);
    }
    DrawCircle(birdBoundingCircle.x,birdBoundingCircle.y,birdBoundingCircle.z,RED);

    EndDrawing();
}

void birdJump(void){
    int boostTime=deltaTime+(jumpTime*fps);
    if(deltaTime<boostTime)
        birdVelocity*=(-1);
    std::cout<<birdVelocity*(-1)<<std::endl;
}