#include "globalVals.h"
#include "Ball.h"
#include <iostream>

#include <random>
#include <math.h>
#include <string>
#include <future>

// false for left side, true for right side
Ball::Ball(bool side) {
    
    std::srand(SDL_GetTicks());

    double theta = rand() % 90;
    theta = side ? theta - 45 : theta + 135;

    theta = theta * M_PI / 180;
    
    totalV = PADDLE_MAX_VELOCITY;

    vx = SDL_cos(theta) * totalV;
    vy = SDL_sin(theta) * totalV;
    
    rect.h = PADDLE_WIDTH * 2;
    rect.w = PADDLE_WIDTH * 2;
    
    px = WINDOW_WIDTH / 2;
    py = WINDOW_HEIGHT / 2;
    rect.x = px;
    rect.y = py;

    color = {255, 255, 255, 0};
}

void playSound(std::string filename) {
    // local variables
        Uint32 wav_length; // length of our sample
        Uint8 *wav_buffer; // buffer containing  audio file
        SDL_AudioSpec wav_spec;
        if(SDL_LoadWAV(filename.c_str(), &wav_spec, &wav_buffer, &wav_length) == NULL){
          return;
        }
        SDL_AudioDeviceID deviceId = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, 0);
        SDL_QueueAudio(deviceId, wav_buffer, wav_length);
        SDL_PauseAudioDevice(deviceId, 0);
        // SDL_Delay(50);

        SDL_CloseAudioDevice(deviceId);
        
        SDL_FreeWAV(wav_buffer);
        std::cout << "bruh" << std::endl;
}

// 2 for normal, 0 for left side loss, 1 for right side loss
int Ball::updatePosition(const int& y1, const int& y2, 
                        const int& v1, const int& v2) {
    std::future<void> handle;
    px += vx;
    py += vy;

    
    // Top and Bottom of screen check
    if (rect.y > WINDOW_HEIGHT - rect.h) {
        py = WINDOW_HEIGHT - rect.h;
        vy *= -1;
    } else if (rect.y < 0) {
        py = 0;
        vy *= -1;
    }

    rect.x = px;
    rect.y = py;

    int paddleBound = 2;
    if (abs(vx) > 10) {paddleBound = 3;}

    // player 1 collision
    if (px <= PADDLE_WIDTH * 2 && px >= PADDLE_WIDTH &&
        y1 + PADDLE_HEIGHT >= py && py >= y1 - rect.h) {
    

            double theta = SDL_atan((v1 + vy)/vx * -1);
            totalV *= 1.1;
            vx = SDL_cos(theta) * totalV;
            vy = SDL_sin(theta) * totalV;
            
            
            px = PADDLE_WIDTH * 2;
            
        }
    
    // player 2 collision
    if (px >= WINDOW_WIDTH - PADDLE_WIDTH * 2 * paddleBound && px <= WINDOW_WIDTH - PADDLE_WIDTH &&
        y2 + PADDLE_HEIGHT >= py && py >= y2 - rect.h) {
            
        
            double theta = SDL_atan(-vx / (v2 + vy));
            totalV *= 1.1;
            vx = SDL_sin(theta) * totalV;
            vy = SDL_cos(theta) * totalV;


            px = WINDOW_WIDTH - PADDLE_WIDTH * 4;
        }



    

    if (px > WINDOW_WIDTH) { return 1; }
    if (px + rect.w < 0) { return 0; }

    return 2;

}

void Ball::draw(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}