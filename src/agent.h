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
    Agent(int grid_width, int grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}
    virtual void Initialize() = 0;
    virtual void Update(Map &map, int &score) = 0;

    Direction direction = Direction::kDown;
    const float speed{0.1f};
    float pos_x;
    float pos_y;
    bool alive{true};
    int grid_width;
    int grid_height;

private:
    // int grid_width;
    // int grid_height;
};
#endif // AGENT_H