#include "WindGenericPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

WindGenericPreview* WindGenericPreview::create()
{
	WindGenericPreview* instance = new WindGenericPreview();

	instance->autorelease();

	return instance;
}

WindGenericPreview::WindGenericPreview()
{
	this->previewHeavenHug = Sprite::create(ObjectResources::Traps_HeavenHug_PreviewHeavenHug);

	this->previewHeavenHug->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewHeavenHug);
}

HackablePreview* WindGenericPreview::clone()
{
	return WindGenericPreview::create();
}

void WindGenericPreview::onEnter()
{
	super::onEnter();

	const float offset = 48.0f;

	this->previewHeavenHug->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));

	this->previewHeavenHug->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(1.5f, Vec2(0.0f, HackablePreview::PreviewRadius - offset))),
			nullptr
		))
	);
}
