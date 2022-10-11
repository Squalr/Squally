#include "SpriterAnimationPart.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationPart::SpriterAnimationPart()
{
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}

void SpriterAnimationPart::addAnimationPartChild(SpriterAnimationPart* part)
{
    part->parentPart = this;
    this->childAnimationParts.push_back(part);
    
    GameUtils::changeParent(part, this, false);
}

void SpriterAnimationPart::clearAnimationPartChildren()
{
    this->childAnimationParts.clear();
}
