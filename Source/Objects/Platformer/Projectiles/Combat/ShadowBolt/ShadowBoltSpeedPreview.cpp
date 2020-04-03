#include "ShadowBoltSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

ShadowBoltSpeedPreview* ShadowBoltSpeedPreview::create()
{
	ShadowBoltSpeedPreview* instance = new ShadowBoltSpeedPreview();

	instance->autorelease();

	return instance;
}

ShadowBoltSpeedPreview::ShadowBoltSpeedPreview()
{
	this->shadowBolt = SmartAnimationSequenceNode::create(FXResources::ShadowBolt_ShadowBolt_0000);

	this->xmm1Left = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));
	this->xmm1Right = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("-1.0f"));

	this->shadowBolt->setScale(0.35f);

	this->previewNode->addChild(this->shadowBolt);
	this->assemblyTextNode->addChild(this->xmm1Left);
	this->assemblyTextNode->addChild(this->xmm1Right);
}

ShadowBoltSpeedPreview::~ShadowBoltSpeedPreview()
{
}

HackablePreview* ShadowBoltSpeedPreview::clone()
{
	return ShadowBoltSpeedPreview::create();
}

void ShadowBoltSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->shadowBolt->setPosition(Vec2(0.0f, 16.0f));

	this->shadowBolt->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - offset), this->shadowBolt->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(HackablePreview::PreviewRadius - offset, this->shadowBolt->getPositionY()))),
			nullptr
		))
	);

	this->shadowBolt->playAnimationRepeat(FXResources::ShadowBolt_ShadowBolt_0000, 0.085f);
}

void ShadowBoltSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;
	
	this->xmm1Left->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, -16.0f));
	this->xmm1Right->setPosition(Vec2(HackablePreview::PreviewRadius - offset, -16.0f));
}
