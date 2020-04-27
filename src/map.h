#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>

enum class Status
{
    kFree,
    kFood,
    kSpecial,
    kWall,
};

class Map
{
public:
    // Constructor / Deconstructor
    Map(int grid_width, int grid_height);
    ~Map();

    // Classical Behaviour
    void Initialize();
    void Print();
    char ParseStatus(Status status);

    // Getter / Setter
    Status GetMapElement(int i, int j) const;
    void SetMapElement(int i, int j, Status status);
    int GetCurrentTotalFood() const { return total_food; }
    void DecreaseTotalFood() { total_food--; }
    void IncreaseTotalFood() { total_food++; }

private:
    std::vector<std::vector<Status>> map;
    int grid_width;
    int grid_height;
    std::ifstream file;
    int total_food = 0;
};

#endif // MAP_H