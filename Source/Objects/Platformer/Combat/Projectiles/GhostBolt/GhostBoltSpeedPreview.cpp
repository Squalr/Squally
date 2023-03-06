#include "GhostBoltSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/FXResources.h"

using namespace cocos2d;

GhostBoltSpeedPreview* GhostBoltSpeedPreview::create()
{
	GhostBoltSpeedPreview* instance = new GhostBoltSpeedPreview();

	instance->autorelease();

	return instance;
}

GhostBoltSpeedPreview::GhostBoltSpeedPreview()
{
	this->fireball = SmartAnimationSequenceNode::create(FXResources::FireBall_FireBall_0000);

	this->xmm1Left = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));
	this->xmm1Right = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("-1.0f"));

	this->fireball->setScale(0.35f);

	this->previewNode->addChild(this->fireball);
	this->assemblyTextNode->addChild(this->xmm1Left);
	this->assemblyTextNode->addChild(this->xmm1Right);
}

GhostBoltSpeedPreview::~GhostBoltSpeedPreview()
{
}

HackablePreview* GhostBoltSpeedPreview::clone()
{
	return GhostBoltSpeedPreview::create();
}

void GhostBoltSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;

	this->fireball->setPosition(Vec2(0.0f, 0.0f));

	this->fireball->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-(HackablePreview::PreviewRadius - offset), this->fireball->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(HackablePreview::PreviewRadius - offset, this->fireball->getPositionY()))),
			nullptr
		))
	);

	this->fireball->playAnimationRepeat(FXResources::FireBall_FireBall_0000, 0.085f);
}

void GhostBoltSpeedPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 64.0f;
	
	this->xmm1Left->setPosition(Vec2(-HackablePreview::PreviewRadius + offset, 32.0f));
	this->xmm1Right->setPosition(Vec2(HackablePreview::PreviewRadius - offset, -32.0f));
}
