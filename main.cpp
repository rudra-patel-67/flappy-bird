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
    rectangles[0] = {(float)widthsection*3-30,0,widthsection,(float)windowHeight};
    rectangles[1] = {(float)widthsection*7-30,0,widthsection,(float)windowHeight};
    // rectangles[2] = {(float)widthsection*5-30,0,widthsection,(float)windowHeight};
    // rectangles[3] = {(float)widthsection*7-30,0,widthsection,(float)windowHeight};
    
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
        // std::cout<<birdBoundingCircle.x<<"\t"<<birdBoundingCircle.y<<"\t"<<birdBoundingCircle.z<<"\t"<<windowWidth<<"\t"<<windowHeight<<std::endl;
    }
    else
    {
        GameOver=true;
    }

    if(IsKeyPressed(KEY_SPACE)){
        boostTime=deltaTime+(jumpTime*fps);
    }
    if(IsKeyDown(KEY_R)){
        birdBoundingCircle.y=(windowHeight/2.0f)-10.0f;
        birdVelocity=5;
        GameOver=false;
    }

    std::cout<<"Delta : "<<deltaTime<<"\t Boost : "<<boostTime<<std::endl;
    if(deltaTime<boostTime){
        birdVelocity=-10;
    }    
    else 
    if(birdVelocity<0 && deltaTime>boostTime){
        birdVelocity=5;
    }

    for(int i=0;i<recCount;i++){
        rectangles[i].x-=3;
        if(rectangles[i].x+rectangles[i].width+widthsection<0){
            rectangles[i].x=windowWidth;
        }
    }

    deltaTime++;


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

    if(GameOver)
    {
        CheckCollisionCircleRec({birdBoundingCircle.x,birdBoundingCircle.y},birdBoundingCircle.z,rectangles[2]);
        DrawText("Game Over", windowWidth/2-80, windowHeight/2-40, 30, BLACK);
    }
    else{
        DrawOjects();
    }

    EndDrawing();
}

void DrawOjects(){
    for(int i=0;i<recCount;i++){
        DrawRectangleRec(rectangles[i],WHITE);
    }
    DrawCircle(birdBoundingCircle.x,birdBoundingCircle.y,birdBoundingCircle.z,RED);
}
