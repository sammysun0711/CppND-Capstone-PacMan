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
    /**
     * Agent Constructor
     * @param grid_width set width of map
     * @param grid_height set height of map
     */
    Agent(size_t grid_width, size_t grid_height)
        : grid_width(grid_width),
          grid_height(grid_height) {}
    /**
     * Initialize agent, must be inmplemented in child class
     */
    virtual void Initialize() = 0;
    /**
     * Update position consider period of map at portal
     * @param new_pos_x define a new agent postion in x-direction to be setted
     * @param new_pos_y define a new agent postion in y-direction to be setted
     */
    void UpdatePos(float new_pos_x, float new_pos_y)
    {
        // Wrap the agent postion around to the beginning if going off of the screen.
        pos_x = fmod(new_pos_x + grid_width, grid_width);
        pos_y = fmod(new_pos_y + grid_height, grid_height);
    }
    Direction currentDir = Direction::kUp;
    float speed{0.1f};
    float pos_x;
    float pos_y;
    size_t grid_width;
    size_t grid_height;
};
#endif // AGENT_H
