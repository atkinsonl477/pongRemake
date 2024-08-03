#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include "Player.h"
#include "Ball.h"

#include <map>

class Engine {
    
private:

    SDL_Window* window;
    SDL_Renderer* renderer;
    
    std::map<int, bool> keyboardMap;
    bool isRunning;
 
    TTF_Font* font;
    Player* p1;
    Player* p2;
    Ball* ball;

public:
    Engine();

    // empties event queue, typically used to grab user input
    void processInput();
    void updatePosition();
    // Renders the new output on screen
    void render();

    bool running() {return isRunning;}


};
