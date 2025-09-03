#pragma once

#include <map>

#include "scripts/Script.h"

class Camera;
class SpriteSheet;

struct Tile
{
    bool isCollider;
    sf::Vector2i spriteSheetOffset;
    sf::Vector2i propSheetOffset;
    sf::Vector2i position;
    bool hasProp;
};

class TilemapEditor : public IScript
{
public:
    TilemapEditor(const char* pathToResource, const char* pathToProps, const char* outputFile);
    void OnStart() override;
    void OnUpdate() override;
    void OnFixedUpdate() override;
    void OnRender(RenderWindow* window) override;
    void DisplaySpiteSheet(RenderWindow* window);
    void UpdateAllArrays();
    
    void GenerateGrid();
    void SaveGrid();

private:

    Camera* mMainCamera;
    sf::Vector2f* mCameraPosition;
    TRANSFORM* mTransform;
    sf::Vector2f movement;
    
    sf::Vector2f mousePosition;

    sf::VertexArray mGridVertices;
    sf::VertexArray mRenderedTilemap;
    sf::VertexArray mRenderedProps;
    sf::VertexArray mRenderedCollider;
    
    sf::RectangleShape mSelector;
    sf::Vector2i mCurrentCase;
    sf::Vector2i mOffset;

    int currentTileIndex = 8;
    std::vector<Tile> tileMap;
    SpriteSheet* spriteSheet = nullptr ;
    SpriteSheet* spriteSheetProps = nullptr ;
    Texture* texture = nullptr ;
    Texture* textureProps = nullptr ;
    std::map<int, Tile> mTiles;

    char pathToSpriteSheet[50];
    char pathToPropsSpriteSheet[50];
    char outputTilemap[50];

    float smoothNavigation = 0.0f;

    bool isPropsEditing;

    // Configuration of current tileset editor (Grid is just visual you can draw out of the grid)
    static constexpr int mapSize = 10000;
    static constexpr int halfMapSize = mapSize/2;
    static constexpr int tileSize = 32;
    static constexpr int tilePerRow = mapSize/tileSize;
    static constexpr int totalTile = tilePerRow*tilePerRow;
};
