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
    /**
     * Map Constructor
     * @param grid_width set width of map
     * @param grid_height set height of map
     * @param filename set path to map file
     */
    Map(int grid_width, int grid_height, std::string filename);
    /**
     * Map Deconstructor
     * Clean up, close opened file
     */
    ~Map();

    // Classical Behaviour
    /**
     * Initialize map by parsing information from given map file
     */
    void Initialize();
    /**
     * Print map in console for debugging
     */
    void Print() const;
    /**
     * Parse status as a char
     * @param status reference to a status instance
     * @return a char for corresponding status, posible char 'W': Wall, 'o': Food, 'O': Pils, 'u': Free
     */
    char ParseStatus(Status const &status) const;

    // Getter / Setter
    /**
     * Get status store in map[i][j]
     * @param status reference to a status instance
     */
    Status GetMapElement(int i, int j) const;
    /**
     * Assgin status in map[i][j]
     */
    void SetMapElement(int i, int j, Status status);
    /**
     * Get current total food in map
     * @return total food in map
     */
    int GetCurrentTotalFood() const { return total_food; }
    /**
     * Decrease total food when pacman eats food
     */
    void DecreaseTotalFood() { total_food--; }
    /**
     * Increase total food during initialization of map
     */
    void IncreaseTotalFood() { total_food++; }

private:
    std::vector<std::vector<Status>> map;
    int grid_width;
    int grid_height;
    std::ifstream file;
    int total_food = 0;
};

#endif // MAP_H