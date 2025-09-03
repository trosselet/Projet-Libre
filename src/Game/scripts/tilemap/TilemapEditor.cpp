#include "pch.h"

#include "TilemapEditor.h"

#include "Colors.h"
#include "Transform.h"

#include "SpriteSheet.h"
#include "ECS/Components/Camera.h"
#include "ECS/Systems/CameraSystem.h"

TilemapEditor::TilemapEditor(const char* pathToResource, const char* pathToProps, const char* outputFile) :
    mMainCamera(nullptr), mCameraPosition(nullptr), mTransform(nullptr),
    mSelector({32, 32}), mOffset({0, 0}), mTiles(), isPropsEditing(false)
{
    strcat_s(pathToSpriteSheet, pathToResource);
    strcat_s(pathToPropsSpriteSheet, pathToProps);
    strcat_s(outputTilemap, outputFile);
}

void TilemapEditor::OnStart()
{
    
    mTransform = owner->GetTransform();
    
    mGridVertices = sf::VertexArray(sf::PrimitiveType::Triangles);
    mRenderedTilemap = sf::VertexArray(sf::PrimitiveType::Triangles);
    mRenderedCollider = sf::VertexArray(sf::PrimitiveType::Triangles);
    mRenderedProps = sf::VertexArray(sf::PrimitiveType::Triangles);

    mOffset.x = halfMapSize;
    mOffset.y = halfMapSize;

    mSelector.setFillColor(sf::Color::Red);

    texture = new Texture(std::string(pathToSpriteSheet), true);
    textureProps = new Texture(std::string(pathToSpriteSheet), true);
    
    spriteSheet = new SpriteSheet(*texture);
    //spriteSheet->Extract(0, 0, 16, 16, 384, 384);
    spriteSheet->Extract(672, 112, 16, 16, 160, 287);

    spriteSheetProps = new SpriteSheet(*textureProps);
    //spriteSheetProps->Extract(0, 288, 16, 16, 288, 96);
	spriteSheetProps->Extract(672, 112, 16, 16, 160, 287);
    
    std::string path;
    std::vector<sf::Vector2f> position;
    std::vector<sf::Vector2f> spriteSheetOffset;
    std::vector<sf::Vector2i> spriteSheetPropOffset;
    std::vector<bool> colliders;
    
    std::string line;
    std::ifstream myfile(outputTilemap);
    if (myfile.good())
    {
        if (myfile.is_open())
        {
            while (getline(myfile, line))
            {
                std::istringstream in(line);
                std::string type;
                in >> type;

                if (type == "t")
                {
                    float x, y, offX, offY;
                    in >> x >> y >> offX >> offY;
                    int propX, propY;
                    in >> propX >> propY;
                    int isCollider;
                    in >> isCollider;

                    position.emplace_back(x, y);
                    spriteSheetOffset.emplace_back(offX, offY);
                    //Debug::Log(std::to_string(isCollider));
                    if (propX >= 0)
                        spriteSheetPropOffset.emplace_back(propX, propY);
                    else
                        spriteSheetPropOffset.emplace_back(-1, -1);

                    if (isCollider >= 0)
                        colliders.push_back(isCollider);
                    else
                        colliders.push_back(false);

                }
                else if (type == "spritesheet_path")
                {
                    in >> path;
                }
                else if (type == "props_path")
                {
                    in >> path;
                }
            }
            myfile.close();
        }
    
        for (int i = 0; i < position.size(); i++)
        {
            sf::Vector2f pos = position[i];
            sf::Vector2f offset = spriteSheetOffset[i];
            sf::Vector2i offsetProps = spriteSheetPropOffset[i];
            bool hasProps = offsetProps.y != -1 && offsetProps.x != -1;

            int currentTileX = pos.x/tileSize * tileSize + 2;
            int currentTileY = pos.y/tileSize * tileSize + 2;
            int index = tilePerRow * (currentTileY/tileSize-2) + (currentTileX/tileSize-2);
            mTiles.emplace(index, Tile{colliders[i], sf::Vector2i(offset), sf::Vector2i(offsetProps),
                                       sf::Vector2i(pos.x, pos.y), hasProps});
        }
        UpdateAllArrays();

    }

    GenerateGrid();
    
}

void TilemapEditor::OnFixedUpdate()
{
    if (movement.x > tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.x < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({-tileSize+.0f, 0.0f}));
        movement = {0, 0};
    } else if (movement.y > tileSize) {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, tileSize+.0f}));
        movement = {0, 0};
    } else if (movement.y < -tileSize)
    {
        mTransform->SetPosition(mTransform->position + sf::Vector2f({0.f, -tileSize+.0f}));
        movement = {0, 0};
    }
}

void TilemapEditor::OnUpdate()
{
    
    mCurrentCase.x = (int)(mousePosition.x/tileSize) * tileSize + 2;
    mCurrentCase.y= (int)(mousePosition.y/tileSize) * tileSize + 2;
    if (isButtonPressed(sf::Mouse::Button::Left))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
        if (isPropsEditing)
        {
            if (!mTiles.contains(index))
            {
                mTiles.emplace(index, Tile(false, sf::Vector2i(0, 0), sf::Vector2i(spriteSheetProps->GetSpriteSheetPart(currentTileIndex)), mCurrentCase, true));
            } else
            {
                mTiles.at(index).hasProp = true;
                mTiles.at(index).propSheetOffset = sf::Vector2i(spriteSheetProps->GetSpriteSheetPart(currentTileIndex));
            }
        }
        else
        {
            if (!mTiles.contains(index))
            {
                mTiles.emplace(index, Tile(false, sf::Vector2i(spriteSheet->GetSpriteSheetPart(currentTileIndex)), sf::Vector2i(0, 0), mCurrentCase));
            } else
            {
                mTiles.at(index).spriteSheetOffset = spriteSheet->GetSpriteSheetPart(currentTileIndex);
            }
        }
        UpdateAllArrays();

    }

    if (isButtonPressed(sf::Mouse::Button::Right))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
        if (mTiles.contains(index))
        {
            if (isPropsEditing)
            {
                mTiles.at(index).hasProp = false;
            } else
            {
                mTiles.erase(index);
            }
        }
        UpdateAllArrays();

    }

    // Movement on tile map
    if (isKeyPressed(sf::Keyboard::Key::D))
    {
        movement += mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Q))
    {
        movement -= mTransform->right * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::S))
    {
        movement += mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }
    if (isKeyPressed(sf::Keyboard::Key::Z))
    {
        movement -= mTransform->up * Engine::GetDeltaTime() * 1000.0f;
    }

    if (isKeyPressed(sf::Keyboard::Key::J))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
        if (!mTiles.contains(index))
        {
            mTiles.emplace(index, Tile(true, sf::Vector2i(spriteSheet->GetSpriteSheetPart(currentTileIndex)), sf::Vector2i(0, 0), mCurrentCase));
        } else
        {
            mTiles.at(index).isCollider = true;
        }
        UpdateAllArrays();
    }

    if (isKeyPressed(sf::Keyboard::Key::K))
    {
        int index = tilePerRow * (mCurrentCase.y/tileSize-2) + (mCurrentCase.x/tileSize-2);
        if (mTiles.contains(index))
        {
            mTiles.at(index).isCollider = false;
        }
        UpdateAllArrays();
    }
    
    if (GetKeyDown(Keyboard::Key::Up))
    {
        isPropsEditing = !isPropsEditing;
        currentTileIndex = 0;
    }

    if (GetKey(Keyboard::Key::Left))
    {
        SpriteSheet* currentSpriteSheet = isPropsEditing ? spriteSheetProps : spriteSheet;
        if (currentTileIndex >= currentSpriteSheet->SpriteCount) currentTileIndex = currentSpriteSheet->SpriteCount-1;
        if (currentTileIndex > 0)
        {
            smoothNavigation += Engine::GetDeltaTime();
            if (smoothNavigation >= 0.1f)
            {
                currentTileIndex = --currentTileIndex%currentSpriteSheet->SpriteCount;
                smoothNavigation = 0.0f;
            }
            if (Keyboard::GetKeyDown(Keyboard::Key::Left)) currentTileIndex = --currentTileIndex%currentSpriteSheet->SpriteCount;
            if (Keyboard::GetKeyUp(Keyboard::Key::Left)) smoothNavigation = 0.0f;
        } else
        {
            currentTileIndex = currentSpriteSheet->SpriteCount-1;
        }

    }
    if (Keyboard::GetKeyUp(Keyboard::Key::Left)) smoothNavigation = 0.0f;


    if (GetKey(Keyboard::Key::Right))
    {
        SpriteSheet* currentSpriteSheet = isPropsEditing ? spriteSheetProps : spriteSheet;
        smoothNavigation += Engine::GetDeltaTime();
        if (smoothNavigation >= 0.1f)
        {
            currentTileIndex = ++currentTileIndex%currentSpriteSheet->SpriteCount;
            smoothNavigation = 0.0f;
        }
        if (Keyboard::GetKeyDown(Keyboard::Key::Right)) currentTileIndex = ++currentTileIndex%currentSpriteSheet->SpriteCount;
        
    }
    if (Keyboard::GetKeyUp(Keyboard::Key::Right)) smoothNavigation = 0.0f;
    // used to zoom out / in
    if (isKeyPressed(sf::Keyboard::Key::Subtract))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor += 1.0f * Engine::GetDeltaTime();
    }

    if (isKeyPressed(sf::Keyboard::Key::Add))
    {
        Engine::GetCameraSystem()->GetActiveCamera()->ZoomFactor -= 1.0f * Engine::GetDeltaTime();
    }

    if (GetKey(Keyboard::LControl) && GetKeyDown(Keyboard::S))
    {
        SaveGrid();
    }
    
}

void TilemapEditor::OnRender(RenderWindow* window)
{
    if (Engine::GetCameraSystem()->GetActiveCamera() != nullptr)
    {
        mMainCamera = Engine::GetCameraSystem()->GetActiveCamera();
        mCameraPosition = &mMainCamera->GetEntity()->GetTransform()->position;
        
        mousePosition = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

        window->draw(mGridVertices);
        window->draw(mRenderedTilemap, texture);
        window->draw(mRenderedProps, textureProps);
        window->draw(mRenderedCollider);

        DisplaySpiteSheet(window);
    
        mSelector.setPosition(sf::Vector2f(mCurrentCase));
        window->draw(mSelector);
    }
}

void TilemapEditor::DisplaySpiteSheet(RenderWindow* window)
{
    SpriteSheet* currentSpriteSheet = isPropsEditing ? spriteSheetProps : spriteSheet;
    if (currentSpriteSheet == nullptr) return;
    int startIndex = currentTileIndex-8 < 0 ? 0 : currentTileIndex-8;
    int position = 0;
    for (int i = startIndex; i < currentSpriteSheet->SpriteCount && i < currentTileIndex+8; i++)
    {
        sf::Vector2f finalPosition = sf::Vector2f(20 + (tileSize*2.0f + 10.0f) * position , 850.0f) + *mCameraPosition;
        if (i == currentTileIndex)
        {
            mSelector.setPosition(finalPosition - sf::Vector2f(3.0f, 3.0f));
            mSelector.scale({1.2f, 1.2f});
            window->draw(mSelector);
            mSelector.setScale({1.0f,1.0f});
        }
        currentSpriteSheet->SetSprite(i);
        currentSpriteSheet->setPosition(finalPosition);
        currentSpriteSheet->setScale({2.0f, 2.0f});
        window->Draw(currentSpriteSheet);
        position++;
    }
}

void TilemapEditor::UpdateAllArrays()
{
    
    mRenderedTilemap.clear();
    mRenderedCollider.clear();
    mRenderedProps.clear();
    for (auto& sprite : mTiles)
    {
        Tile pSprite = sprite.second;
        sf::Vector2f pos = sf::Vector2f(pSprite.position);
        sf::Vector2f offset = sf::Vector2f(pSprite.spriteSheetOffset);
        
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y), sf::Color::White, offset+sf::Vector2f(16.0f, 0.0f)));
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offset+sf::Vector2f(16.0f, 16.0f)));
            
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 32), sf::Color::White, offset+sf::Vector2f(0.0f, 16.0f)));
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offset+sf::Vector2f(16.0f, 16.0f)));
        mRenderedTilemap.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));

        if (pSprite.hasProp)
        {
            sf::Vector2f offsetProp = sf::Vector2f(pSprite.propSheetOffset);

            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offsetProp));
            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 0.0f)));
            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 16.0f)));
            
            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(0.0f, 16.0f)));
            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 16.0f)));
            mRenderedProps.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offsetProp));
        }
        
        if (pSprite.isCollider)
        {
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), Colors::transparent_gray));
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y), Colors::transparent_gray));
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), Colors::transparent_gray));
            
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 32), Colors::transparent_gray));
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), Colors::transparent_gray));
            mRenderedCollider.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), Colors::transparent_gray));
        }
    }
    
}

void TilemapEditor::GenerateGrid()
{
    for (int x = 0; x <= tilePerRow; x++)
    {
        int tileX = x * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, 0), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX+2, mapSize), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(tileX, 0), sf::Color::White));
    }
    
    for (int y = 0; y <= tilePerRow; y++) {
        int tileY = y * tileSize;
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
            
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(mapSize, tileY+2), sf::Color::White));
        mGridVertices.append(sf::Vertex(sf::Vector2f(0, tileY), sf::Color::White));
    }
    
}

void TilemapEditor::SaveGrid()
{
    std::filesystem::create_directories("../../res/Tiles/saved/");
    std::string toWrite;
    for (auto& tile : mTiles)
    {
        sf::Vector2i tilePosition = tile.second.position;
        sf::Vector2i spriteSheetOffset = tile.second.spriteSheetOffset;
        // Default Tile Data
        toWrite += "t " + std::to_string(tilePosition.x) + " "
            + std::to_string(tilePosition.y) + " "
            + std::to_string(spriteSheetOffset.x) + " "
            + std::to_string(spriteSheetOffset.y) + " ";

        // Sprite Sheet Props
        sf::Vector2i spriteSheetPropOffset = tile.second.hasProp ? tile.second.propSheetOffset : sf::Vector2i(-1, -1);
        toWrite += std::to_string(spriteSheetPropOffset.x) + " "
            + std::to_string(spriteSheetPropOffset.y) + " ";

        // Is colliding
        toWrite += std::to_string(tile.second.isCollider);
        
        toWrite += "\n";
    }
    std::string path(pathToSpriteSheet);
    toWrite += "spritesheet_path " + path;
    
    std::ofstream saveFile(outputTilemap);
    saveFile.clear();
    saveFile << toWrite;
    saveFile.close();
}
