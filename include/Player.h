#include "Paddle.h"
#include "SDL2/SDL_ttf.h"
#include <map>

class Player {

public:

    /*
    \param side Defines the side of the screen. false for left, true for right (default left)
    \param isBot Defines if movement is automatic (default is false)
    */
    Player(bool side = false, bool isBot = false, SDL_Color color = {255, 255, 255, 0});
    

    void updatePosition(std::map<int, bool>& keyboardMap, const int& bally = WINDOW_HEIGHT / 2);

    void drawPlayer(SDL_Renderer* renderer, TTF_Font* font);

    void incScore() { score++; }

    int& getY() { return paddle->getY(); }
    int& getV() { return paddle->getV(); }

private:

    SDL_Color color;
    Paddle* paddle;
    int score;
    bool isBot;
    bool side;

};