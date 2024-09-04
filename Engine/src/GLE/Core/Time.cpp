//
// Created by Andrew Graser on 8/28/2024.
//

#include "Time.h"
#include "GLFW/glfw3.h"


namespace GLE {
    float Time::mTime = 0.0f;
    float Time::mLastFrame = 0.0f;


    void Time::Init() {
        mTime = 0.0f;
        mLastFrame = 0.0f;
    }

    void Time::Update() {
        float curTime = (float)glfwGetTime();
        mTime = curTime - mLastFrame;
        mLastFrame = curTime;
    }
}