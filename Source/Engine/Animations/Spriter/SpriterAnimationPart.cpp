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

void SpriterAnimationPart::setRelativePosition(const Vec2& relativePosition)
{
    this->relativePosition = relativePosition;

    this->setPosition(this->relativePosition);
}

void SpriterAnimationPart::setHeirarchyScale(const Vec2& scale)
{
    this->heirarchyScale = scale;
}

void SpriterAnimationPart::cascadeScales(Vec2 scale)
{
    this->setPosition(this->relativePosition * scale);

    scale *= this->heirarchyScale;

	for (SpriterAnimationPart* child : this->childAnimationParts)
	{
		child->cascadeScales(scale);
	}
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
