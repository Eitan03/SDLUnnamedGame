#pragma once
#include <iostream>
#include <exception>

#include <MyGraphicsLibrary/Point.h>

typedef unsigned int ID;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

struct GameEngineException : public std::exception {
    GameEngineException(std::string msg): _msg(msg) {  }
    const char* what() const throw () {
        return _msg.c_str();
    }

private:
    std::string _msg;
};


enum Direction {
    None = 0,
    Up = 1,
    Down = 2,
    Left = 4,
    Right = 8,
};
