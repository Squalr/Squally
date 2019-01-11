#include "SetAnglePreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SetAnglePreview* SetAnglePreview::create()
{
	SetAnglePreview* instance = new SetAnglePreview();

	instance->autorelease();

	return instance;
}

SetAnglePreview::SetAnglePreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
}

HackablePreview* SetAnglePreview::clone()
{
	return SetAnglePreview::create();
}

void SetAnglePreview::onEnter()
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
