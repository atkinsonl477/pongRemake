# include "Engine.h"
# include "globalVals.h"
# include "SDL2/SDL_ttf.h"
# include <iostream>
# include <map>

using std::cout, std::cerr, std::endl;
Engine::Engine() {


    if (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0) {
        cerr << "Could not initialize Subsystems";
        throw std::uncaught_exception();
    }
    

    window = SDL_CreateWindow("Pong", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
    isRunning = true;
    if (window == nullptr) {
        cerr << "Could not Create Window" << endl;
        isRunning = false;
    }


    font = TTF_OpenFont("./src/Assets/Helvetica.ttc", 64);
    if (font == nullptr) {
        cerr << "Font not found";
        isRunning =false;
    }

    p1 = new Player(false, false, {0, 255, 0, 0});  
    p2 = new Player(true, true, {255, 0, 0, 0}); 
    ball = new Ball(true);

}

void Engine::processInput() {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        switch (e.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                keyboardMap[e.key.keysym.sym] = true;
                // cout << "Key pressed!!" << endl;
                break;
            case SDL_KEYUP:
                keyboardMap[e.key.keysym.sym] = false;
                // cout << "Key released!!" << endl;
                break;
            default:
                break;

        }
        // cout << e.type << endl;
    }
}

void Engine::updatePosition() {

    // Reset ball because I dont wanna deal with it
    if (keyboardMap[SDLK_r]) {
        delete ball;
        ball = new Ball(true);
    }
   
    p1->updatePosition(keyboardMap);
    p2->updatePosition(keyboardMap, ball->getY());

    int ret = ball->updatePosition(p1->getY(), p2->getY(), 
                                    p1->getV(), p2->getV());
    if (ret == 0) {
        p2->incScore();
        delete ball;
        ball = new Ball(false);
    }
    if (ret == 1) {
        p1->incScore();
        delete ball;
        ball = new Ball(true);
    }
}


void Engine::render() {
    SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);

    p1->drawPlayer(renderer, font);
    p2->drawPlayer(renderer, font);
    ball->draw(renderer);

    

    SDL_RenderPresent(renderer);


    SDL_RenderClear(renderer);
    

    if (!isRunning) {
        cout << "closing engine..." << endl;
        
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
    }
}