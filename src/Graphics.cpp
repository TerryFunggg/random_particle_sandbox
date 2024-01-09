#include "Graphics.h"
#include "SDL2/SDL_pixels.h"
#include "SDL2/SDL_rect.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL_surface.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_video.h"
#include <iostream>
#include <ostream>

SDL_Window* Graphics::window = NULL;
SDL_Renderer* Graphics::renderer = NULL;
int Graphics::windowWidth = 1280;
int Graphics::windowHeight = 960;

TTF_Font* Graphics::sans;
SDL_Texture* Graphics::font_texture = NULL;

int Graphics::Width() {
    return windowWidth;
}

int Graphics::Height() {
    return windowHeight;
}

bool Graphics::OpenWindow() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL" << std::endl;
        return false;
    }

    if (windowWidth + windowHeight == 0) {
        SDL_DisplayMode display_mode;
        SDL_GetCurrentDisplayMode(0, &display_mode);
        windowWidth = display_mode.w;
        windowHeight = display_mode.h;
    }


    window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
    if (!window) {
        std::cerr << "Error creating SDL window" << std::endl;
        return false;
    }
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        std::cerr << "Error creating SDL renderer" << std::endl;
        return false;
    }
    if(TTF_Init() != 0) {
        std::cout << TTF_GetError()  << std::endl;
        return false;
    }

    sans = TTF_OpenFont("Roboto-Bold.ttf", 14);
    if(!sans) {
        std::cout << TTF_GetError()  << std::endl;
        return false;
    }
    return true;
}

void Graphics::ClearScreen(Uint32 color) {
    SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
    SDL_RenderClear(renderer);
}

void Graphics::RenderFrame() {
    SDL_RenderPresent(renderer);
}

void Graphics::DrawFillCircle(int x, int y, int radius, Uint32 color) {
    filledCircleColor(renderer, x, y, radius, color);
}

void Graphics::DrawMsg(int x, int y, char* msg) {

    SDL_Color white = {255, 255, 255};

    SDL_Surface* surface_msg = TTF_RenderText_Solid(sans, msg, white);

    font_texture = SDL_CreateTextureFromSurface(renderer, surface_msg);

    SDL_Rect rec;
    rec.x = x;
    rec.y = y;
    rec.h = 90 * (windowWidth / windowHeight);
    rec.w =  240 * (windowWidth / windowHeight);

    SDL_RenderCopy(renderer, font_texture,NULL, &rec);

    SDL_FreeSurface(surface_msg);

}


void Graphics::CloseWindow(void) {
    SDL_DestroyTexture(font_texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

}
