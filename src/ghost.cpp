#include <cmath>
#include <iostream>
#include <vector>

#include "ghost.h"
#include "map.h"
void Ghost::Initialize()
{
    switch (ghost_colour)
    {
    case Colour::kRed:
        pos_x = 14.0f;
        pos_y = 15.0f;
        currentDir = Direction::kLeft;
        mode = Mode::kChase;
        prev_mode = Mode::kChase;
        break;
    case Colour::kBlue:
        pos_x = 15.0f;
        pos_y = 15.0f;
        currentDir = Direction::kRight;
        mode = Mode::kScatter;
        prev_mode = Mode::kScatter;
        break;
    case Colour::kYellow:
        pos_x = 16.0f;
        pos_y = 15.0f;
        currentDir = Direction::kDown;
        mode = Mode::kScatter;
        prev_mode = Mode::kScatter;
        break;
    case Colour::kPink:
        pos_x = 17.0f;
        pos_y = 15.0f;
        currentDir = Direction::kUp;
        mode = Mode::kChase;
        prev_mode = Mode::kChase;
        break;
    default:
        break;
    }
    eaten = false;
}

void Ghost::Move(PacMan const &pacman, Map const &map)
{
    if (pacman.IsPowered())
    {
        SetFrighten(map);
    }
    else
    {
        if (IsEaten())
        {
            MoveTowardPen(map);
        }
        else
        {
            ResumePrevMode();
            GetTarget(pacman);
            MoveTowardTarget(map);
        }
    }
    Update(map);
}
void Ghost::GetTarget(PacMan const &pacman)
{
    switch (mode)
    {
    case Mode::kChase:
        switch (ghost_colour)
        {
        case Colour::kRed:
            target = {pacman.GetPacBlockX(),
                      pacman.GetPacBlockY()};
            break;
        case Colour::kBlue:
            switch (pacman.currentDir)
            {
            case Direction::kLeft:
                target = {
                    pacman.GetPacBlockX() - 2,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kRight:
                target = {
                    pacman.GetPacBlockX() + 2,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kUp:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() - 2};
                break;
            case Direction::kDown:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() + 2};
                break;
            default:
                target = {pacman.GetPacBlockX(),
                          pacman.GetPacBlockY()};
                break;
            }
            break;
        case Colour::kYellow:
            target = {0, 0};
            break;
        case Colour::kPink:
            switch (pacman.currentDir)
            {
            case Direction::kLeft:
                target = {
                    pacman.GetPacBlockX() - 4,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kRight:
                target = {
                    pacman.GetPacBlockX() + 4,
                    pacman.GetPacBlockY()};
                break;
            case Direction::kUp:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() - 4};
                break;
            case Direction::kDown:
                target = {
                    pacman.GetPacBlockX(),
                    pacman.GetPacBlockY() + 4};
                break;
            default:
                target = {pacman.GetPacBlockX(),
                          pacman.GetPacBlockY()};
                break;
            }
            break;
        }
        break;
    case Mode::kScatter:
        switch (ghost_colour)
        {
        case Colour::kRed:
            target = {28, 0};
            break;
        case Colour::kBlue:
            target = {28, 31};
            break;
        case Colour::kYellow:
            target = {0, 31};
            break;
        case Colour::kPink:
            target = {0, 0};
            break;
        default:
            break;
        }
        break;

    default:
        break;
    }
}

void Ghost::SetSpeed()
{
    if (mode == Mode::kFrighten)
    {
        speed = 0.05f;
    }
    else
    {
        speed = 0.1f;
    }
}

int Ghost::CheckJuncs(Map const &map)
{
    int exit = 0;
    if (!IsWall(Direction::kLeft, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kRight, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kUp, map))
    {
        exit++;
    }
    if (!IsWall(Direction::kDown, map))
    {
        exit++;
    }
    return exit;
}

bool Ghost::IsAtCenter()
{
    return (static_cast<int>(GetGhostX() * 10.0f) % 10 == 0 || static_cast<int>(GetGhostX() * 10.0f) % 10 == 9) &&
           (static_cast<int>(GetGhostY() * 10.0f) % 10 == 0 || static_cast<int>(GetGhostY() * 10.0f) % 10 == 9);
}

float Ghost::CalcDistance(int x, int y)
{
    return std::sqrt(std::pow(target.x - x, 2) + std::pow(target.y - y, 2));
}
void Ghost::MoveTowardTarget(Map const &map)
{
    float distance = 999.0f;
    Direction tempDir = currentDir;
    if (CheckJuncs(map) >= 3 && IsAtCenter())
    {
        if (currentDir != Direction::kDown && !IsWall(Direction::kUp, map))
        {
            float d = CalcDistance(GetGhostBlockX(), GetGhostBlockY() - 1);
            if (d < distance)
            {
                tempDir = Direction::kUp;
                distance = d;
            }
        }

        if (currentDir != Direction::kLeft && !IsWall(Direction::kRight, map))
        {
            float d = CalcDistance(GetGhostBlockX() + 1, GetGhostBlockY());
            if (d < distance)
            {
                tempDir = Direction::kRight;
                distance = d;
            }
        }

        if (currentDir != Direction::kRight && !IsWall(Direction::kLeft, map))
        {
            float d = CalcDistance(GetGhostBlockX() - 1, GetGhostBlockY());
            if (d < distance)
            {
                tempDir = Direction::kLeft;
                distance = d;
            }
        }
        if (currentDir != Direction::kUp && !IsWall(Direction::kDown, map))
        {
            float d = CalcDistance(GetGhostBlockX(), GetGhostBlockY() - 1);
            if (d < distance)
            {
                tempDir = Direction::kDown;
                distance = d;
            }
        }
        currentDir = tempDir;
    }
    else
    {
        CornerHandle(map);
    }
}

void Ghost::CornerHandle(Map const &map)
{
    if (IsAtCenter())
    {
        if (IsWall(currentDir, map))
        {
            if (!IsWall(Direction::kLeft, map) && currentDir != Direction::kRight)
            {
                currentDir = Direction::kLeft;
            }
            else if (!IsWall(Direction::kUp, map) && currentDir != Direction::kDown)
            {
                currentDir = Direction::kUp;
            }
            else if (!IsWall(Direction::kRight, map) && currentDir != Direction::kLeft)
            {
                currentDir = Direction::kRight;
            }
            else
            {
                currentDir = Direction::kDown;
            }
        }
    }
}
void Ghost::SetFrighten(Map const &map)
{
    // prev_mode = mode;
    mode = Mode::kFrighten;
    CornerHandle(map);
}

void Ghost::ResumePrevMode()
{
    mode = prev_mode;
    if (InPen())
    {
        eaten = false;
    }
}

void Ghost::SetDeath()
{
    eaten = true;
    mode = Mode::kDeath;
}

void Ghost::MoveTowardPen(Map const &map)
{
    if (GetGhostX() <= 13.55 && GetGhostX() >= 13.45 && GetGhostY() >= 15.5f && GetGhostY() <= 20.0f)
    {
        MoveInPen(map);
    }
    else
    {
        target = {15, 15};
        MoveTowardTarget(map);
    }
    Update(map);
}

bool Ghost::InPen()
{
    if (GetGhostX() >= 12.0f && GetGhostX() <= 17.0f && GetGhostY() >= 14.0f && GetGhostY() < 17.0f)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void Ghost::MoveInPen(Map const &map)
{
    // Initially check they have the correct X coordinates
    if (GetGhostX() <= 14.5f && GetGhostX() >= 13.5f)
    {
        if (GetGhostY() >= 18.95f)
        {
            currentDir = Direction::kDown;
        }
        else if (GetGhostY() <= 17.0f)
        {
            currentDir = Direction::kUp;
        }
    }
    else
    {
        // If they dont have the correct x coordinate
        // Determine if they need to move left or right
        if (GetGhostX() < 13.5f)
        {
            currentDir = Direction::kRight;
        }
        else if (GetGhostX() > 14.5f)
        {
            currentDir = Direction::kLeft;
        }
    }
}

void Ghost::Update(Map const &map)
{
    SetSpeed();
    float new_pos_x = pos_x;
    float new_pos_y = pos_y;
    switch (currentDir)
    {
    case Direction::kUp:
        new_pos_y -= speed;
        break;

    case Direction::kDown:
        new_pos_y += speed;
        break;

    case Direction::kLeft:
        new_pos_x -= speed;
        break;

    case Direction::kRight:
        new_pos_x += speed;
        break;
    }

    Status status = GetNextStatus(currentDir, map);
    switch (status)
    {
    case Status::kFree:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kFood:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kPill:
        UpdatePos(new_pos_x, new_pos_y);
        break;
    case Status::kWall:
        break;
    default:
        break;
    }
}

bool Ghost::IsWall(Direction const &dir, Map const &map)
{
    return GetNextStatus(dir, map) == Status::kWall;
}

Status Ghost::GetNextStatus(Direction const &dir, Map const &map)
{
    switch (dir)
    {
    case Direction::kLeft:
        return GetStatus(GetGhostX() - GetSpeed(), GetGhostY(), map);
        break;
    case Direction::kRight:
        return GetStatus(GetGhostX() + GetSpeed(), GetGhostY(), map);
        break;
    case Direction::kUp:
        return GetStatus(GetGhostX(), GetGhostY() - GetSpeed(), map);
        break;
    case Direction::kDown:
        return GetStatus(GetGhostX(), GetGhostY() + GetSpeed(), map);
        break;
    default:
        std::cout << "Error: Unknown Direction\n";
        break;
    }
}

Status Ghost::GetStatus(float x, float y, Map const &map)
{
    int block_x = static_cast<int>(std::floor(fmod(x + grid_width, grid_width)));
    int block_y = static_cast<int>(std::floor(fmod(y + grid_height, grid_height)));
    return map.GetMapElement(block_x, block_y);
}
