#include "PendulumBladeSetAnglePreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

PendulumBladeSetAnglePreview* PendulumBladeSetAnglePreview::create()
{
	PendulumBladeSetAnglePreview* instance = new PendulumBladeSetAnglePreview();

	instance->autorelease();

	return instance;
}

PendulumBladeSetAnglePreview::PendulumBladeSetAnglePreview()
{
	this->previewBlade = Sprite::create(ObjectResources::Traps_PendulumBlade_PreviewBlade);

	this->eax0Degrees = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("0"));
	this->eax90Degrees = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("90"));
	this->eax180Degrees = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("180"));
	this->eax270Degrees = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, ConstantString::create("270"));

	this->previewBlade->setAnchorPoint(Vec2(0.5f, 1.0f));

	this->previewNode->addChild(this->previewBlade);
	this->assemblyTextNode->addChild(this->eax0Degrees);
	this->assemblyTextNode->addChild(this->eax90Degrees);
	this->assemblyTextNode->addChild(this->eax180Degrees);
	this->assemblyTextNode->addChild(this->eax270Degrees);
}

HackablePreview* PendulumBladeSetAnglePreview::clone()
{
	return PendulumBladeSetAnglePreview::create();
}

void PendulumBladeSetAnglePreview::onEnter()
{
	super::onEnter();

	this->previewBlade->setRotation(0.0f);

	this->previewBlade->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(RotateTo::create(1.5f, 270.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 180.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 90.0f)),
			EaseSineInOut::create(RotateTo::create(1.5f, 0.0f)),
			nullptr
		))
	);
}

void PendulumBladeSetAnglePreview::initializePositions()
{
	super::initializePositions();

	const float offset = 24.0f;

	this->eax0Degrees->setPosition(Vec2(HackablePreview::PreviewRadius - offset, 0.0f));
	this->eax90Degrees->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset));
	this->eax180Degrees->setPosition(Vec2(-(HackablePreview::PreviewRadius - offset), 0.0f));
	this->eax270Degrees->setPosition(Vec2(0.0f, -(HackablePreview::PreviewRadius - offset)));
}
