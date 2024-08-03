# include "Paddle.h"
# include "globalVals.h"


Paddle::Paddle(bool side, int y , SDL_Color color) {
    rect.h = PADDLE_HEIGHT;
    rect.w = PADDLE_WIDTH;
    rect.x = side ? WINDOW_WIDTH - PADDLE_WIDTH * 2 : PADDLE_WIDTH;
    rect.y = y;
    this->color = color;
}


void Paddle::drawPaddle(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
}

void Paddle::move() {

    rect.y += v;
    if (rect.y <= PADDLE_WIDTH) rect.y = PADDLE_WIDTH;
    if (rect.y >= WINDOW_HEIGHT - PADDLE_WIDTH - PADDLE_HEIGHT) 
        rect.y = WINDOW_HEIGHT - PADDLE_WIDTH - PADDLE_HEIGHT;
}

