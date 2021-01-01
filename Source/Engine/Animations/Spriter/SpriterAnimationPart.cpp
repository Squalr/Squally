#include "SpriterAnimationPart.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationPart::SpriterAnimationPart()
{
    this->heirarchyScale = Vec2::ONE;
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}

void SpriterAnimationPart::setHeirarchyScale(const Vec2& scale)
{
    this->heirarchyScale = scale;
}

Vec2 SpriterAnimationPart::getHeirarchyScale()
{
    return this->heirarchyScale;
}

Vec2 SpriterAnimationPart::getFullHeirarchyScale()
{
    SpriterAnimationPart* parent = GameUtils::getParentAsType<SpriterAnimationPart>(this);
    Vec2 parentScale = (parent == nullptr ? Vec2::ONE : parent->getFullHeirarchyScale());

    return Vec2(this->heirarchyScale.x * parentScale.x, this->heirarchyScale.y * parentScale.y);
}
