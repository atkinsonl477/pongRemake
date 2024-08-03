#include "Player.h"
#include "SDL2/SDL_ttf.h"
#include <string>
#include <iostream>

Player::Player(bool side, bool isBot, SDL_Color color) {
    paddle = new Paddle(side, WINDOW_HEIGHT / 2 - PADDLE_HEIGHT / 2, color);
    score = 0;
    this->isBot = isBot;
    this->side = side;
    this->color = color; 
}

void Player::updatePosition(std::map<int, bool>& keyboardMap, const int& bally) {
    
    // Bot Logic : if far away, move closer. Advanced, I know.
    if (isBot) {
        int currPos = paddle->getY() + PADDLE_HEIGHT / 2;

      
        if (bally <= currPos - PADDLE_HEIGHT/4 ) {
            paddle->setV(-PADDLE_MAX_VELOCITY);
        }
        else if (bally >= currPos + PADDLE_HEIGHT/4 ){
            paddle->setV(PADDLE_MAX_VELOCITY);
        }
        else {
            paddle->setV(0);
        }
    }
    else {
        if (keyboardMap[SDLK_w]) {
            paddle->setV(-PADDLE_MAX_VELOCITY);
        }
        if (keyboardMap[SDLK_s]) {
            paddle->setV(PADDLE_MAX_VELOCITY);
        }
        if (!keyboardMap[SDLK_w] && !keyboardMap[SDLK_s]) {
            paddle->setV(0);
        }
    }

    paddle->move();
    
}



void Player::drawPlayer(SDL_Renderer* renderer, TTF_Font* font) {
    paddle->drawPaddle(renderer);
    std::string score_text = std::to_string(score);        
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), color);
    SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
    int text_width = textSurface->w;
    int text_height = textSurface->h;
    SDL_FreeSurface(textSurface);
    int pos = side ? WINDOW_WIDTH * 3 / 4 : WINDOW_WIDTH / 4;
    SDL_Rect renderQuad = { pos, PADDLE_WIDTH, text_width, text_height };
    SDL_RenderCopy(renderer, text, NULL, &renderQuad);
    SDL_DestroyTexture(text);
    
}