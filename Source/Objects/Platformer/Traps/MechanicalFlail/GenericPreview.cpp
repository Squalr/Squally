#include "GenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

GenericPreview* GenericPreview::create()
{
	GenericPreview* instance = new GenericPreview();

	instance->autorelease();

	return instance;
}

GenericPreview::GenericPreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_MechanicalFlail_PreviewFlail);

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
}

HackablePreview* GenericPreview::clone()
{
	return GenericPreview::create();
}

void GenericPreview::onEnter()
{
	super::onEnter();

	this->previewBlade->setRotation(45.0f);

	this->previewBlade->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(1.5f, 315.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 45.0f)),
			nullptr
		))
	);
}
