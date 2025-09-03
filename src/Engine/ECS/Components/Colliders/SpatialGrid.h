#pragma once

#include <unordered_map>
#include <vector>

struct CellCoords {
    int x, y;

    bool operator==(const CellCoords& other) const
    {
        return x == other.x && y == other.y;
    }
};

struct CellHash {
    std::size_t operator()(const CellCoords& key) const
    {
        return std::hash<int>()(key.x) ^ std::hash<int>()(key.y);
    }
};

class SpatialGrid
{
public:
    SpatialGrid(float cellSize);
    ~SpatialGrid();

    void UpdateEntity(Entity* entity);
    
    CellCoords GetCellCoords(float x, float y) const;

    void GetNeighboringEntities(int cellX, int cellY, std::vector<Entity*>& outEntities);

    std::vector<Entity*> GetEntitiesInCell(int x, int y);

    std::unordered_map<CellCoords, std::vector<Entity*>, CellHash>& GetAllCells() { return mCells; }

    // Get All Grid Info
    float GetCellSize() const { return mCellSize; }

private:
    float mCellSize; // Size of a Cell
    std::unordered_map<CellCoords, std::vector<Entity*>, CellHash> mCells; 
};