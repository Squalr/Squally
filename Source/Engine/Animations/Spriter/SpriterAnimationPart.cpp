#include "SpriterAnimationPart.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationPart::SpriterAnimationPart()
{
	this->childAnimationParts = std::vector<SpriterAnimationPart*>();
    this->heirarchyScale = Vec2::ONE;
}

SpriterAnimationPart::~SpriterAnimationPart()
{
}

void SpriterAnimationPart::addAnimationPartChild(SpriterAnimationPart* part)
{
    this->childAnimationParts.push_back(part);
    
    GameUtils::changeParent(part, this, false);
}

void SpriterAnimationPart::clearAnimationPartChildren()
{
    this->childAnimationParts.clear();
}
