#include "WaterballSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

WaterballSpeedPreview* WaterballSpeedPreview::create()
{
	WaterballSpeedPreview* instance = new WaterballSpeedPreview();

	instance->autorelease();

	return instance;
}

WaterballSpeedPreview::WaterballSpeedPreview()
{
	this->waterball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->xmm1Left = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));
	this->xmm1Right = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("-1.0f"));

	this->waterball->setScale(0.35f);

	this->previewNode->addChild(this->waterball);
	this->assemblyTextNode->addChild(this->xmm1Left);
	this->assemblyTextNode->addChild(this->xmm1Right);
}

WaterballSpeedPreview::~WaterballSpeedPreview()
{
}

HackablePreview* WaterballSpeedPreview::clone()
{
	return WaterballSpeedPreview::create();
}

void WaterballSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->waterball->setPosition(Vec2(0.0f, 0.0f));

	this->waterball->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - offset), this->waterball->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(HackablePreview::PreviewRadius - offset, this->waterball->getPositionY()))),
			nullptr
		))
	);

	this->waterball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void WaterballSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 64.0f;
	
	this->xmm1Left->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, 32.0f));
	this->xmm1Right->setPosition(Vec2(HackablePreview::PreviewRadius - offset, -32.0f));
}
