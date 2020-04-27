#ifndef PACMAN_H
#define PACMAN_H

#include <vector>
#include "SDL.h"
#include <cmath>
#include <agent.h>
#include <ghost.h>
class Ghost;
class PacMan : public Agent
{
public:
  // Constuctor / Deconstructor
  PacMan(size_t grid_width, size_t grid_height)
      : Agent(grid_width, grid_height)
  {
    Initialize();
  }

  // Classical Behaviour
  void Initialize() override;
  void Move(Map &map, int &score, int frame_counter);
  bool CheckCollision(Ghost &ghost, bool &running, int &score);

  // Getter / Setter
  float GetPacX() const { return pos_x; }
  float GetPacY() const { return pos_y; }
  int GetPacBlockX() const { return static_cast<int>(std::floor(GetPacX())); }
  int GetPacBlockY() const { return static_cast<int>(std::floor(GetPacY())); }
  bool IsPowered() const { return powered; }
  bool SetDeath() { alive = false; }
  bool IsAlive() const { return alive; }

private:
  // Classical Behaviour
  void UpdatePos(float new_pos_x, float new_pos_y);

  // Member Variable
  bool powered{false};
  int powered_start_frame;
  int powered_end_frame;
  static constexpr int powered_periode = 10 * 60;
  bool alive{true};
};

#endif // PACMAN_H
