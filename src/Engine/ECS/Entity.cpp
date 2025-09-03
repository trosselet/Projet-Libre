#include "pch.h"

#include "ECS.h"
#include "Engine.h"
#include "Transform.h"
#include "scripts/ScriptManager.h"

int Entity::sNextId = 0;

Entity::Entity(int layer) : Bitmask(0), mCreated(false), mDestoyed(false), mEnabled(true), mId(sNextId), mIndex(0),
                            mLayer(layer), mTransform(new TRANSFORM(nullptr))
{
    mTag = Tag::NONE;
    sNextId++;
}

Entity::Entity(Entity* parent, int layer) : Bitmask(0),
                                            mCreated(false), mDestoyed(false), mEnabled(true), mId(sNextId), mIndex(0),
                                            mLayer(layer), mTransform(new TRANSFORM(parent))
{
    parent->GetTransform()->AddChild(this);
    mTag = Tag::NONE;
    sNextId++;
}

Entity::~Entity()
{
    if (mTransform)
        delete mTransform;
}

void Entity::AddBitmask(int mask)
{
    Bitmask = Bitmask | mask;
}

void Entity::RemoveBitmask(int mask)
{
    Bitmask = Bitmask & ~(mask);
}

void Entity::SetIndex(int index)
{
    mIndex = index;
}

int Entity::GetId()
{
    return mId;
}

int* Entity::GetIndex()
{
    return &mIndex;
}

void Entity::Create(int index)
{
    mIndex = index;
    mCreated = true;
}

void Entity::Destroy()
{
    mDestoyed = true;
    for (auto child : GetTransform()->GetChildList())
    {
        child->Destroy();
    }
}

bool Entity::IsEnable()
{
    return mEnabled;
}

void Entity::SetEnabled(bool state)
{
    mEnabled = state;
    for (auto child : GetTransform()->GetChildList())
    {
        child->SetEnabled(state);
    }
}

bool Entity::IsCreated() const
{
    return mCreated;
}

bool Entity::IsDestroyed() const
{
    return mDestoyed;
}
