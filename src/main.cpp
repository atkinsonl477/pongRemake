# include <iostream>
# include "Engine.h"

# include "SDL2/SDL.h"




int main(int argc, char* argv[]) {



    Engine* Game = new Engine();

    while (Game->running()) {
        Uint32 begin = SDL_GetTicks();
        
        Game->processInput();
        Game->updatePosition();
        Game->render();

        Uint32 diff = SDL_GetTicks() - begin;

        if (IDEAL_FRAME_TIME_MS - diff > 0) {
            SDL_Delay(IDEAL_FRAME_TIME_MS - diff);
            // std::cout << "Frame time: " << diff << "ms" << std::endl;
        }
        
        
    }

    

    return 0;
}
