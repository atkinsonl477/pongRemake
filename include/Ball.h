#include "SDL2/SDL.h"
#include <string>



class Ball {

public:

    Ball(bool side);

    // void playSound(std::string filename);

    // 2 for normal, 0 for left side loss, 1 for right side loss
    int updatePosition(const int& y1, const int& y2, const int& v1, const int& v2);

    void draw(SDL_Renderer* renderer);

    
    const int& getY() {return rect.y;}

private:

    SDL_Rect rect;
    SDL_Color color;
    double vx;
    double vy;

    double px;
    double py;

    // totalV is used to find the magnitude of the ball vector
    double totalV;

};