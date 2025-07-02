#include "./raylib/include/raylib.h"
#include <string>
#include <iostream>
int windowWidth = 720;
int windowHeight = 1080;
int fps = 60;
bool GameOver=false;

int deltaTime;

int birdVelocity = 5;
int jumpTime = 1;


Vector3 birdBoundingCircle;


std::string windowTitle;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------

void UpdateDrawFrame(void);     // Update and Draw one frame
void birdJump(void);
// bool exitWindowRequested = false;   // Flag to request window to exit
// bool exitWindow = false;
