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
	this->entityRef = entity;

	this->previewAnimation = SmartAnimationNode::create(this->animationResource);

	this->previewAnimation->setScale(this->scale * 0.25f);

	this->previewNode->addChild(this->previewAnimation);
}

EntityPreview::~EntityPreview()
{
}

HackablePreview* EntityPreview::clone()
{
	return EntityPreview::create(this->entityRef);
}

void EntityPreview::onEnter()
{
	super::onEnter();
}

void EntityPreview::initializePositions()
{
	super::initializePositions();
}
