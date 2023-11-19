#include "engine.hpp"

Engine::Engine(int w, int h)
{
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
      "Conway's Game", 
      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
      w, h, 0 
    );

    if ( !window )
    {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
      exit(1);
    }

    // VSync is necessary for good performance, without it the rendering loop will try to render infinite fps
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if ( !renderer )
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
        exit(1);
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, w, h);

    if ( !texture ) {
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", SDL_GetError());
      exit(1);
    }
}

Engine::~Engine()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Engine::SetColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Engine::ClearScreen() 
{
    SDL_RenderClear(renderer);
}

void Engine::DrawLine(SDL_Point start, SDL_Point end)
{
    SDL_RenderDrawLineF(renderer, (float)start.x, (float)start.y, (float)end.x, (float)end.y);
}

void Engine::FillRect(SDL_FRect rect)
{
    SDL_RenderFillRectF(renderer, &rect);
}

void Engine::FillRects(std::vector<SDL_FRect>& rects)
{
    if( rects.size() == 0 ) return;
    SDL_FRect* rectArray = &rects[0];
    SDL_RenderFillRectsF(renderer, rectArray, rects.size());
}

void Engine::Render()
{
    SDL_RenderPresent(renderer);
}
