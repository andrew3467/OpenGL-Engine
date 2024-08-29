//
// Created by Andrew Graser on 8/28/2024.
//

#ifndef OPENGL_ENGINE_TIME_H
#define OPENGL_ENGINE_TIME_H


namespace GLE {
    class Time {
    public:
        static void Init();

        static void Update();


        static const float GetTime() {return mTime;}


    private:
        static float mTime;
        static float mLastFrame;
    };
}

#endif //OPENGL_ENGINE_TIME_H
