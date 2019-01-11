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
	this->previewHeavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);

	this->previewHeavenHug->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewHeavenHug);
}

HackablePreview* HeavenHugGenericPreview::clone()
{
	return HeavenHugGenericPreview::create();
}

void HeavenHugGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 24.0f;

	this->previewHeavenHug->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));

	this->previewHeavenHug->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}
