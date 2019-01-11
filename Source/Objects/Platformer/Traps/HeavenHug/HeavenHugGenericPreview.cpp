#include "HeavenHugGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

HeavenHugGenericPreview* HeavenHugGenericPreview::create()
{
	HeavenHugGenericPreview* instance = new HeavenHugGenericPreview();

	instance->autorelease();

	return instance;
}

HeavenHugGenericPreview::HeavenHugGenericPreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
}

HackablePreview* HeavenHugGenericPreview::clone()
{
	return HeavenHugGenericPreview::create();
}

void HeavenHugGenericPreview::onEnter()
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
