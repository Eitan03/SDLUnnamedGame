#pragma once
//timer.h

#include <SDL.h> //for Uint32

namespace MGL {
    class Timer
    {
    public:
        Timer();
        ~Timer();

        bool Started();
        bool Paused();

        void Start();
        void Pause();
        void Stop();
        void Continue();

        int GetTime();

    private:
        int ticks;
        int pauseTime;
        int startingTime;

        bool started;
        bool paused;
    };
}

