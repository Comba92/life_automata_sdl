#pragma once
#include <SDL2/SDL.h>
#include <vector>

class Engine
{
  public:
    Engine(int w, int h);
    ~Engine();

    void SetColor(SDL_Color color);
    void ClearScreen();
    void DrawLine(SDL_Point start, SDL_Point end);
    void FillRect(SDL_FRect rect);
    void FillRects(std::vector<SDL_FRect>& rects);
    void Render();

  private:
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* texture = NULL;
};