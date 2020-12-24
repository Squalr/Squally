#include "SpriterAnimationSprite.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/Spriter/SpriterAnimationBone.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

SpriterAnimationSprite* SpriterAnimationSprite::create(std::string spriteResource, Vec2 anchor)
{
	SpriterAnimationSprite* instance = new SpriterAnimationSprite(spriteResource, anchor);

	instance->autorelease();

	return instance;
}

SpriterAnimationSprite::SpriterAnimationSprite(std::string spriteResource, Vec2 anchor)
{
	this->sprite = Sprite::create(spriteResource);

	// Not super useful since we just overwrite this during animation events
	this->sprite->setAnchorPoint(anchor);

	this->addChild(this->sprite);
}

SpriterAnimationSprite::~SpriterAnimationSprite()
{
}

void SpriterAnimationSprite::setAnchorPoint(const Vec2& anchorPoint)
{
	this->sprite->setAnchorPoint(anchorPoint);
}

/*
void SpriterAnimationSprite::setScaleX(float scaleX)
{
	SpriterAnimationBone* parent = GameUtils::getFirstParentOfType<SpriterAnimationBone>(this);

	while (parent != nullptr)
	{
		scaleX *= parent->getBoneScale().x;
		parent = GameUtils::getFirstParentOfType<SpriterAnimationBone>(parent);
	}

    super::setScaleX(scaleX);
}

void SpriterAnimationSprite::setScaleY(float scaleY)
{
	SpriterAnimationBone* parent = GameUtils::getFirstParentOfType<SpriterAnimationBone>(this);

	while (parent != nullptr)
	{
		scaleY *= parent->getBoneScale().y;
		parent = GameUtils::getFirstParentOfType<SpriterAnimationBone>(parent);
	}

    super::setScaleY(scaleY);
}
*/

void SpriterAnimationSprite::visit(Renderer* renderer, const Mat4& parentTransform, uint32_t parentFlags)
{
    _selfFlags |= parentFlags;

    // quick return if not visible. children won't be drawn.
    if (!_visible || (_displayedOpacity == 0 && _cascadeOpacityEnabled))
    {
        return;
    }
    
    if(_selfFlags & FLAGS_DIRTY_MASK)
    {
        _modelViewTransform = parentTransform * getNodeToParentTransform();
    }

    // self draw
    this->draw(renderer, _modelViewTransform, _selfFlags);

    const int size = _children.size();

    this->sortAllChildren();

    for (int index = 0; index < size; index++)
    {
        _children[index]->visit(renderer, _modelViewTransform, _selfFlags);
    }

	_selfFlags = 0;
}
