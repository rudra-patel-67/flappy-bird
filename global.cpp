#include "./raylib/include/raylib.h"
#include <string>
#include <iostream>
int windowWidth = 720;
int windowHeight = 1080;
int fps = 60;
bool GameOver=false;
int widthsection = windowWidth/6;

int deltaTime;

int birdVelocity = 5;
float jumpTime = 0.25;
int boostTime=0;

const int recCount = 2; 
Rectangle rectangles[recCount];

Vector3 birdBoundingCircle;


std::string windowTitle;

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------

void UpdateDrawFrame(void);     // Update and Draw one frame
void birdJump(void);
void DrawOjects();
// bool exitWindowRequested = false;   // Flag to request window to exit
// bool exitWindow = false;
