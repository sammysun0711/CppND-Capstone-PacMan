#ifndef GHOST_H
#define GHOST_H

#include <vector>
#include "SDL.h"
#include "map.h"
#include "pacman.h"
#include <agent.h>

enum class Mode
{
    kChase,
    kScatter,
    kFrighten,
    kLeave,
    kDeath,
    kPen
};

enum class Colour
{
    kRed = 0,
    kBlue = 1,
    kPink = 2,
    kYellow = 3
};
class PacMan;
class Ghost : public Agent
{
public:
    // Constructor / Deconstructor
    Ghost(size_t grid_width, size_t grid_height, Colour colour)
        : Agent{grid_width, grid_height},
          ghost_colour(colour)
    {
        Initialize();
    }
    // Classical Behaviour
    void Initialize() override;
    void Move(PacMan const &pacman, Map const &map);
    void GetTarget(PacMan const &pacman);
    void CornerHandle(Map const &map);
    void MoveTowardTarget(Map const &map);
    void MoveTowardPen(Map const &map);
    void MoveInPen(Map const &map);
    void Update(Map const &map);
    bool IsEaten() const { return eaten; }

    // Getter / Setter
    Colour GetColour() const { return ghost_colour; }
    Mode GetMode() const { return mode; }
    void SetDeath();
    void SetFrighten(Map const &map);

private:
    // Classical Behaviour
    void UpdatePos(float new_pos_x, float new_pos_y);
    bool IsWall(Direction const &dir, Map const &map);
    Status GetNextStatus(Direction const &dir, Map const &map);
    Status GetStatus(float x, float y, Map const &map);
    int CheckJuncs(Map const &map);
    bool IsAtCenter();
    float CalcDistance(int x, int y);
    bool InPen();
    void ResumePrevMode();

    // Getter / Setter
    float GetGhostX() const { return pos_x; }
    float GetGhostY() const { return pos_y; }
    int GetGhostBlockX() const { return static_cast<int>(std::floor(GetGhostX())); }
    int GetGhostBlockY() const { return static_cast<int>(std::floor(GetGhostY())); }
    float GetSpeed() const { return speed; };
    void SetSpeed();

    Mode mode = Mode::kChase;
    Mode prev_mode = Mode::kChase;
    Colour ghost_colour = Colour::kRed;
    SDL_Point target;
    bool eaten;
};

#endif // GHOST_H