#include <cmath>
#include "logic.hpp"

float normalize(int p) {
    return floor(p / BLOCK_SIZE * BLOCK_SIZE);
}

const SDL_Color colorBackground = {22, 22, 22, 255}; // Barely Black
const SDL_Color colorLine = {44, 44, 44, 255}; // Dark grey
const SDL_Color colorGhostCursor = {44, 44, 44, 255}; // Barely grey
const SDL_Color colorActiveBlock = {255, 255, 255, 255}; // White

int main(int argv, char** args) 
{

    Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);
    SparseMatrix board;

    SDL_Event event;
    SDL_bool loop = SDL_TRUE;
    SDL_bool mouseHover = SDL_FALSE;
    SDL_bool mouseClicking = SDL_FALSE;
    SDL_bool addingMode = SDL_FALSE;
    SDL_bool computeGens = SDL_FALSE;
    int timer = 0;
    int countedFrames = 0;

    SDL_FRect rGhostCursor = { SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE };
    

    while(loop) 
    {
        int x,y;
        while( SDL_PollEvent(&event) )
        {
            if( event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP )
            {
                int x = (int)normalize(event.motion.x);
                int y = (int)normalize(event.motion.y);
                
                rGhostCursor.x = (float)x;
                rGhostCursor.y = (float)y;
                
                if(event.type == SDL_MOUSEBUTTONDOWN)
                {
                    mouseClicking = SDL_TRUE;
                    if(board.is_present({x,y})) addingMode = SDL_FALSE;
                    else addingMode = SDL_TRUE;
                }

                if(mouseClicking)
                {
                    if(addingMode) board.add_point({x,y});
                    else board.delete_point({x,y});
                }

                if(event.type == SDL_MOUSEBUTTONUP)
                {
                    mouseClicking = SDL_FALSE;
                    addingMode = SDL_FALSE;
                }
            }

            else switch(event.type)
            {
                case SDL_KEYDOWN:
                    if( event.key.keysym.scancode == SDL_SCANCODE_SPACE )
                    {
                        computeGens = (computeGens == SDL_TRUE) ? SDL_FALSE : SDL_TRUE;
                        timer = SDL_GetTicks();
                    }
                    break;

                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_ENTER)
                        mouseHover = SDL_TRUE;
                    else if(event.window.event == SDL_WINDOWEVENT_LEAVE)
                        mouseHover = SDL_FALSE;
                    break;

                case SDL_QUIT: 
                    loop = SDL_FALSE; 
                    break;
            }
        }

        if( computeGens && timer + ANIMATION_INTERVAL <= SDL_GetTicks() )
        {
            board.nextGeneration();
            timer = SDL_GetTicks();
        }

        engine.SetColor(colorBackground);
        engine.ClearScreen();

        engine.SetColor(colorLine);
        for( int x=BLOCK_SIZE; x <= SCREEN_WIDTH; x += BLOCK_SIZE )
            engine.DrawLine( {x, 0}, {x, SCREEN_HEIGHT} );
        for( int y=BLOCK_SIZE; y <= SCREEN_HEIGHT; y += BLOCK_SIZE )
            engine.DrawLine( {0, y}, {SCREEN_WIDTH, y} );

        if(mouseHover)
        {
            engine.SetColor(colorGhostCursor);
            engine.FillRect(rGhostCursor);
        }

        engine.SetColor(colorActiveBlock);
        std::vector<SDL_FRect> rActiveRects;
        for(auto p : board.points) 
        {
            rActiveRects.push_back( {(float)p.first, (float)p.second, BLOCK_SIZE, BLOCK_SIZE} );
        }
        engine.FillRects(rActiveRects);
        engine.Render();
        countedFrames = (countedFrames+1) % INT_MAX; 
    }
 
    return 0;
}
