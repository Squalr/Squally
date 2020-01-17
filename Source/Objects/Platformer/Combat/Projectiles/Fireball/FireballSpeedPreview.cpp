#include "FireballSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

FireballSpeedPreview* FireballSpeedPreview::create()
{
	FireballSpeedPreview* instance = new FireballSpeedPreview();

	instance->autorelease();

	return instance;
}

FireballSpeedPreview::FireballSpeedPreview()
{
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->xmm1Left = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("-1.0f"));
	this->xmm1Right = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));

	this->fireball->setScale(0.35f);

	this->previewNode->addChild(this->fireball);
	this->assemblyTextNode->addChild(this->xmm1Left);
	this->assemblyTextNode->addChild(this->xmm1Right);
}

HackablePreview* FireballSpeedPreview::clone()
{
	return FireballSpeedPreview::create();
}

void FireballSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->fireball->setPosition(Vec2(0.0f, 16.0f));

	this->fireball->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - offset), this->fireball->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(HackablePreview::PreviewRadius - offset, this->fireball->getPositionY()))),
			nullptr
		))
	);

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void FireballSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;
	
	this->xmm1Left->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, -16.0f));
	this->xmm1Right->setPosition(Vec2(HackablePreview::PreviewRadius - offset, -16.0f));
}
