#pragma once
#include <SDL2/SDL.h>
#include <vector>

// 640x480 4:3, 1280x960 16:9, 
inline constexpr int SCREEN_WIDTH = 1280;
inline constexpr int SCREEN_HEIGHT = 960;
inline constexpr int BLOCK_SIZE = 20;

inline constexpr int COLS = SCREEN_WIDTH / BLOCK_SIZE;
inline constexpr int ROWS = SCREEN_HEIGHT / BLOCK_SIZE;
inline constexpr int ANIMATION_INTERVAL = 100;

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