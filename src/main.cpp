#include <cmath>
#include <SDL2/SDL.h>
#include "definitions.hpp"
#include "logic.hpp"
#include "engine.hpp"

float normalize(int p) {
    return floor(p / BLOCK_SIZE) * BLOCK_SIZE;
}

const SDL_Color colorBackground = {22, 22, 22, 255}; // Barely Black
const SDL_Color colorLine = {44, 44, 44, 255}; // Dark grey
const SDL_Color colorGhostCursor = {44, 44, 44, 255}; // Barely grey
const SDL_Color colorActiveBlock = {255, 255, 255, 255}; // White

typedef struct CursorState{
  SDL_bool isHovering;
  SDL_bool isClicking;
  SDL_bool addingMode;
  SDL_FRect rGhostCursor;
} CursorState;

void handleMouse(SDL_Event event, CursorState& cursor, SparseMatrix& board) {
  int x = (int)normalize(event.motion.x);
  int y = (int)normalize(event.motion.y);

  cursor.rGhostCursor.x = (float)x;
  cursor.rGhostCursor.y = (float)y;

  if (event.type == SDL_MOUSEBUTTONDOWN)
  {
    cursor.isClicking = SDL_TRUE;

    if (board.is_present({x, y}))
      cursor.addingMode = SDL_FALSE;
    else
      cursor.addingMode = SDL_TRUE;
  }

  if (cursor.isClicking)
  {
    if (cursor.addingMode)
      board.add_point({x, y});
    else
      board.delete_point({x, y});
  }

  if (event.type == SDL_MOUSEBUTTONUP)
  {
    cursor.isClicking = SDL_FALSE;
    cursor.addingMode = SDL_FALSE;
  }
}

void DrawRowsAndCols(Engine &engine)
{
  engine.SetColor(colorLine);
  for (int x = BLOCK_SIZE; x <= SCREEN_WIDTH; x += BLOCK_SIZE)
    engine.DrawLine({x, 0}, {x, SCREEN_HEIGHT});
  for (int y = BLOCK_SIZE; y <= SCREEN_HEIGHT; y += BLOCK_SIZE)
    engine.DrawLine({0, y}, {SCREEN_WIDTH, y});
}

int main(int, char**) {
  Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);
  SparseMatrix board;

  SDL_bool shouldClose = SDL_FALSE;

  SDL_FRect rGhostCursor = {SCREEN_WIDTH, SCREEN_HEIGHT, BLOCK_SIZE, BLOCK_SIZE};
  CursorState mouse = {
      .isHovering = SDL_FALSE,
      .isClicking = SDL_FALSE,
      .addingMode = SDL_FALSE,
      rGhostCursor,
  };

  SDL_bool computeGens = SDL_FALSE;
  unsigned int timer = 0;

  SDL_Event event;
  while(!shouldClose) {
    while( SDL_PollEvent(&event) ) {
      switch(event.type) {
      case SDL_MOUSEMOTION:
      case SDL_MOUSEBUTTONDOWN:
      case SDL_MOUSEBUTTONUP:
        handleMouse(event, mouse, board);
      
      case SDL_WINDOWEVENT:
        if (event.window.event == SDL_WINDOWEVENT_ENTER)
          mouse.isHovering = SDL_TRUE;
        else if (event.window.event == SDL_WINDOWEVENT_LEAVE)
          mouse.isHovering = SDL_FALSE;
        break;

      case SDL_KEYDOWN:
        if( event.key.keysym.scancode == SDL_SCANCODE_SPACE )
          computeGens = (computeGens == SDL_TRUE) ? SDL_FALSE : SDL_TRUE;
        

        if ( event.key.keysym.scancode == SDL_SCANCODE_Q ||
        event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) 
          shouldClose = SDL_TRUE;
        break;

      case SDL_QUIT: 
        shouldClose = SDL_TRUE; 
        break;
      }
    }

    if( computeGens && timer >= ANIMATION_FRAMES_DELAY) {
      timer = 0;
      board.next_generation();
    }

    engine.SetColor(colorBackground);
    engine.ClearScreen();

    DrawRowsAndCols(engine);

    if(mouse.isHovering) {
      engine.SetColor(colorGhostCursor);
      engine.FillRect(rGhostCursor);
    }

    engine.SetColor(colorActiveBlock);
    std::vector<SDL_FRect> rActiveRects;
    for(auto p : board.points) {
      rActiveRects.push_back( {(float)p.first, (float)p.second, BLOCK_SIZE, BLOCK_SIZE} );
    }
    engine.FillRects(rActiveRects);

    engine.Render();
    timer++;
  }
 
  return 0;
}
