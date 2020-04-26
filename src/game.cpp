#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : pacman(grid_width, grid_height),
      ghost(grid_width, grid_height),
      map(grid_width, grid_height) {}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  map.Initialize();
  map.Print();

  while (running && map.GetCurrentTotalFood() != 0)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, pacman);
    Update();
    renderer.Render(pacman, ghost, map);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::Update()
{
  if (!pacman.alive)
    return;
  pacman.Update(map, score);
  ghost.Update(map, score);

  // Check if pacman collide with any of ghost
  int p_x = static_cast<int>(pacman.pos_x);
  int p_y = static_cast<int>(pacman.pos_y);
  int g_x = static_cast<int>(ghost.pos_x);
  int g_y = static_cast<int>(ghost.pos_y);
  if (p_x == g_x && p_y == g_y)
  {
    pacman.alive = false;
    running = false;
  }
}

int Game::GetScore() const { return score; }
