#include "ThrownObjectGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

ThrownObjectGenericPreview* ThrownObjectGenericPreview::create(Node* object)
{
	ThrownObjectGenericPreview* instance = new ThrownObjectGenericPreview(object);

	instance->autorelease();

	return instance;
}

ThrownObjectGenericPreview::ThrownObjectGenericPreview(Node* object)
{
	this->object = object;

	this->previewNode->addChild(this->object);
}

ThrownObjectGenericPreview::~ThrownObjectGenericPreview()
{
}

HackablePreview* ThrownObjectGenericPreview::clone()
{
	if (dynamic_cast<Sprite*>(this->object) != nullptr)
	{
		Texture2D* texture = dynamic_cast<Sprite*>(this->object)->getTexture();

		if (texture != nullptr)
		{
			return ThrownObjectGenericPreview::create(Sprite::create(texture->getPath()));
		}
	}
	else if (dynamic_cast<SmartAnimationNode*>(this->object) != nullptr)
	{
		return ThrownObjectGenericPreview::create(dynamic_cast<SmartAnimationNode*>(this->object)->clone());
	}
	else if (dynamic_cast<SmartAnimationSequenceNode*>(this->object) != nullptr)
	{
		return ThrownObjectGenericPreview::create(dynamic_cast<SmartAnimationSequenceNode*>(this->object)->clone());
	}

	return ThrownObjectGenericPreview::create(Node::create());
}

void ThrownObjectGenericPreview::onEnter()
{
	super::onEnter();

	this->object->runAction(RepeatForever::create(RotateBy::create(1.0f, 360.0f)));
}

void ThrownObjectGenericPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 48.0f;

	this->object->setPosition(Vec2(0.0f, 0.0f));
}
