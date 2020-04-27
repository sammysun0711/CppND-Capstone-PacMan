#ifndef AGENT_H
#define AGENT_H
#include <map.h>
class Agent
{
public:
    enum class Direction
    {
        kUp,
        kDown,
        kLeft,
        kRight
    };
    Agent(size_t grid_width, size_t grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}
    virtual void Initialize() = 0;

    Direction currentDir = Direction::kUp;
    float speed{0.1f};
    float pos_x;
    float pos_y;
    bool alive{true};
    size_t grid_width;
    size_t grid_height;

private:
    // int grid_width;
    // int grid_height;
};
#endif // AGENT_H