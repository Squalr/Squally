#include "EntityPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

EntityPreview* EntityPreview::create(PlatformerEntity* entity)
{
	EntityPreview* instance = new EntityPreview(entity);

	instance->autorelease();

	return instance;
}

EntityPreview::EntityPreview(PlatformerEntity* entity)
{
	this->animationResource = entity == nullptr ? "" : entity->getAnimationResource();
	this->scale = entity == nullptr ? 1.0f : entity->getScale();
	this->offset = entity == nullptr ? Vec2::ZERO : Vec2(0.0f, -(entity->getEntitySize() * this->scale).height / 2.0f);
	this->entityClone = entity->uiClone();
	this->previewAnimation = SmartAnimationNode::create(this->animationResource);

	this->previewAnimation->setScale(this->scale * 0.75f);

	this->entityClone->setVisible(false);

	this->previewNode->addChild(this->entityClone);
	this->previewNode->addChild(this->previewAnimation);
}

EntityPreview::~EntityPreview()
{
}

HackablePreview* EntityPreview::clone()
{
	return EntityPreview::create(this->entityClone);
}

void EntityPreview::onEnter()
{
	super::onEnter();

	this->previewAnimation->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(0.5f));
}

void EntityPreview::initializePositions()
{
	super::initializePositions();

	this->previewAnimation->setPosition(this->offset);
}
