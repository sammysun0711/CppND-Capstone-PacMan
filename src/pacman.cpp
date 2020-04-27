#include <cmath>
#include <iostream>

#include "map.h"
#include "pacman.h"

void PacMan::Initialize()
{
  pos_x = 9.0f;
  pos_y = 16.0f;
}

void PacMan::Update(Map &map, int &score)
{
  float new_pos_x = pos_x;
  float new_pos_y = pos_y;
  switch (currentDir)
  {
  case Direction::kUp:
    // std::cout << "kUp\n";
    new_pos_y -= speed;
    break;

  case Direction::kDown:
    // std::cout << "kDown\n";
    new_pos_y += speed;
    break;

  case Direction::kLeft:
    // std::cout << "kLeft\n";
    new_pos_x -= speed;
    break;

  case Direction::kRight:
    // std::cout << "kRight\n";
    new_pos_x += speed;
    break;
  default:
    break;
  }
  int block_x = static_cast<int>(fmod(new_pos_x + grid_width, grid_width));
  int block_y = static_cast<int>(fmod(new_pos_y + grid_height, grid_height));
  Status status = map.GetMapElement(block_x, block_y);
  // std::cout << map.ParseStatus(status) << std::endl;
  switch (status)
  {
  case Status::kFree:
    // std::cout << "[kFree] prev position [" << pos_x << "," << pos_y << "]\n";
    UpdatePos(new_pos_x, new_pos_y);
    // std::cout << "[kFree] new  position [" << pos_x << "," << pos_y << "]\n";

    break;
  case Status::kFood:
    // std::cout << "[kFood] prev position [" << pos_x << "," << pos_y << "]\n";
    // map.SetMapElement(static_cast<int>(new_pos_x), static_cast<int>(new_pos_y), Status::kFree);
    map.SetMapElement(block_x, block_y, Status::kFree);
    map.DecreaseTotalFood();
    UpdatePos(new_pos_x, new_pos_y);
    // std::cout << "[kFood] new  position [" << pos_x << "," << pos_y << "]\n";
    score++;
    // map.SetMapElement(new_pos_x, new_pos_y, Status::kFree);
    break;
  case Status::kSpecial:
    map.SetMapElement(block_x, block_y, Status::kFree);
    map.DecreaseTotalFood();
    UpdatePos(new_pos_x, new_pos_y);
  case Status::kWall:
    // UpdatePos(prev_pos_x, prev_pos_y);
    // std::cout << "[kWall] prev position [" << pos_x << "," << pos_y << "]\n";
    // std::cout << "[kWall] new  position [" << pos_x << "," << pos_y << "]\n";
    break;
  default:
    break;
  }
}

void PacMan::UpdatePos(float new_pos_x, float new_pos_y)
{
  // Wrap the PacMan around to the beginning if going off of the screen.
  pos_x = fmod(new_pos_x + grid_width, grid_width);
  pos_y = fmod(new_pos_y + grid_height, grid_height);
}