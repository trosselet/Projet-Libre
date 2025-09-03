#include "pch.h"
#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(Entity* parent, Sprite* sprite, Shader* shader)
: Component(parent), Image(sprite), RendererShader(shader)
{
    Image->setOrigin({0, 0});
}


SpriteRenderer::~SpriteRenderer(){}

int SpriteRenderer::GetBitmask()
{
    return BITMASK;
}
