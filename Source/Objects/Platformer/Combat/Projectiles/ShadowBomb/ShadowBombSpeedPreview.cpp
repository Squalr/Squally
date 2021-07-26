#include "ShadowBombSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ShadowBombSpeedPreview* ShadowBombSpeedPreview::create()
{
	ShadowBombSpeedPreview* instance = new ShadowBombSpeedPreview();

	instance->autorelease();

	return instance;
}

ShadowBombSpeedPreview::ShadowBombSpeedPreview()
{
	this->shadowBomb = SmartAnimationSequenceNode::create(FXResources::ShadowBomb_ShadowBomb_0000);

	this->xmm1Left = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));
	this->xmm1Right = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("-1.0f"));

	this->shadowBomb->setFlippedX(true);
	this->shadowBomb->setScale(0.35f);

	this->previewNode->addChild(this->shadowBomb);
	this->assemblyTextNode->addChild(this->xmm1Left);
	this->assemblyTextNode->addChild(this->xmm1Right);
}

ShadowBombSpeedPreview::~ShadowBombSpeedPreview()
{
}

HackablePreview* ShadowBombSpeedPreview::clone()
{
	return ShadowBombSpeedPreview::create();
}

void ShadowBombSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->shadowBomb->setPosition(Vec2(0.0f, 16.0f));

	this->shadowBomb->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - offset), this->shadowBomb->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(HackablePreview::PreviewRadius - offset, this->shadowBomb->getPositionY()))),
			nullptr
		))
	);

	this->shadowBomb->playAnimationRepeat(FXResources::ShadowBomb_ShadowBomb_0000, 0.085f);
}

void ShadowBombSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;
	
	this->xmm1Left->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, -16.0f));
	this->xmm1Right->setPosition(Vec2(HackablePreview::PreviewRadius - offset, -16.0f));
}
