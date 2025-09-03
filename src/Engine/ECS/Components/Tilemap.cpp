#include "pch.h"
#include "Tilemap.h"

#include <fstream>

#include "ObjectFactory.h"
#include "Colliders/AABBCollider.h"
#include "Render/Texture.h"
#include "Utils/Debug.h"

class Debug;

Tilemap::Tilemap(Entity* entity, std::string pathToTilemap) : Component(entity)
{

    std::string path;
    
    std::vector<sf::Vector2f> position;
    std::vector<sf::Vector2f> spriteSheetOffset;
    std::vector<sf::Vector2i> spriteSheetPropOffset;
    std::vector<bool> colliders;
    
    std::string line;
    std::ifstream myfile(pathToTilemap);
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
        }
        myfile.close();
    }

    TilemapTexture = new Texture(path, true);
    VertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
    PropsVertexArray.setPrimitiveType(sf::PrimitiveType::Triangles);
    
    VertexArray.clear();
    PropsVertexArray.clear();
    for (int i = 0; i < position.size(); i++)
    {
        sf::Vector2f pos = position[i];
        sf::Vector2f offset = spriteSheetOffset[i];
        bool collider = colliders[i];
        
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y), sf::Color::White, offset+sf::Vector2f(16.0f, 0.0f)));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offset+sf::Vector2f(16.0f, 16.0f)));
            
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 32), sf::Color::White, offset+sf::Vector2f(0.0f, 16.0f)));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offset+sf::Vector2f(16.0f, 16.0f)));
        VertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offset));

        sf::Vector2f offsetProp = sf::Vector2f(spriteSheetPropOffset[i]);
        if (offsetProp.x != -1)
        {

            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offsetProp));
            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 0.0f)));
            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 16.0f)));
            
            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(0.0f, 16.0f)));
            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x+32, pos.y + 32), sf::Color::White, offsetProp+sf::Vector2f(16.0f, 16.0f)));
            PropsVertexArray.append(sf::Vertex(sf::Vector2f(pos.x, pos.y), sf::Color::White, offsetProp));
        }

        if (collider)
        {
            Entity* tileContainer = ObjectFactory::CreateEntity<Entity>();
            tileContainer->GetTransform()->SetPosition(pos);
            tileContainer->SetTag(Entity::Tag::GROUND);
            AABBCollider* tileCollider = ObjectFactory::CreateComponent<AABBCollider>(tileContainer, 0, 0, 32, 32);
            tileCollider->SetStatic(true);
        }
        
    }
    
}

Tilemap::~Tilemap()
{
    delete TilemapTexture;
}

int Tilemap::GetBitmask()
{
    return BITMASK;
}
