#include "SDL2/SDl.h"
#include "globalVals.h"
class Paddle {

public:
    /*
    \param side Defines the side of the screen. 0 for left, 1 for right (default left)
    \param y coordinate (default is middle)
    \param color color of paddle (default is white)
    */
    Paddle(bool side = 0, int y = WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, SDL_Color color = {255, 255, 255, 0});

    
    void drawPaddle(SDL_Renderer* renderer);

    int& getY() { return rect.y; }

    int& getV() { return v; }

    void setV(int v) { this->v = v; }

    
    void move();


private:
    SDL_Rect rect;
    SDL_Color color;
    int v;

};