#pragma once

struct V2f
{
    float x;
    float y;
};

struct Rect
{
    float x;
    float y;
    float w;
    float h;
};

class Player
{
public:
    Player() = default;
    Player(int mapWidth, int mapHeight, int tileSize)
        : levelWidth(mapWidth), levelHeight(mapHeight), tileSize(tileSize)
    {}

public:
    void Update();
    void Draw();
    void Move(float x, float y);
    Rect GetRect() const { return {pos.x, pos.y, size.x, size.y}; }
    int Left() const { return pos.x / tileSize; }
    int Right() const { return (pos.x + size.x) / tileSize; }
    int Top() const { return pos.y / tileSize; }
    int Bottom() const { return (pos.y + size.y) / tileSize; }

private:
    void Input();

public:
    V2f pos;
    V2f oldPos; // used in the past
    V2f vel;
    V2f size;

private:
    int levelWidth;
    int levelHeight;
    int tileSize;
    const float speed = 3;
};
