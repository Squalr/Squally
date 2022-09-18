#include "CrusherSetSpeedPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CrusherSetSpeedPreview* CrusherSetSpeedPreview::create()
{
	CrusherSetSpeedPreview* instance = new CrusherSetSpeedPreview();

	instance->autorelease();

	return instance;
}

CrusherSetSpeedPreview::CrusherSetSpeedPreview()
{
	this->previewCrusher100 = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);
	this->previewCrusher200 = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);
	this->previewCrusher400 = Sprite::create(ObjectResources::Traps_SpikedCrusher_Pole);

	this->eax100Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("100f"));
	this->eax200Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("200f"));
	this->eax400Height = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, true, ConstantString::create("400f"));

	this->previewNode->addChild(this->previewCrusher100);
	this->previewNode->addChild(this->previewCrusher200);
	this->previewNode->addChild(this->previewCrusher400);
	this->assemblyTextNode->addChild(this->eax100Height);
	this->assemblyTextNode->addChild(this->eax200Height);
	this->assemblyTextNode->addChild(this->eax400Height);
}

CrusherSetSpeedPreview::~CrusherSetSpeedPreview()
{
}

HackablePreview* CrusherSetSpeedPreview::clone()
{
	return CrusherSetSpeedPreview::create();
}

void CrusherSetSpeedPreview::onEnter()
{
	super::onEnter();

	const float speed = 1.5f;
	const float offset = 48.0f;
	const float topOffset = 48.0f;

	this->previewCrusher100->setPosition(Vec2(-96.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewCrusher400->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - offset - topOffset));
	this->previewCrusher200->setPosition(Vec2(96.0f, HackablePreview::PreviewRadius - offset - topOffset));

	this->previewCrusher100->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher100->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 4.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher100->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewCrusher200->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher200->getPositionX(), -(HackablePreview::PreviewRadius - offset) / 2.0f))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher200->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);

	this->previewCrusher400->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher400->getPositionX(), -(HackablePreview::PreviewRadius - offset)))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(this->previewCrusher400->getPositionX(), HackablePreview::PreviewRadius - offset - topOffset))),
			nullptr
		))
	);
}

void CrusherSetSpeedPreview::initializePositions()
{
	super::initializePositions();

	this->eax100Height->setPosition(Vec2(-112.0f, HackablePreview::PreviewRadius - 48.0f));
	this->eax400Height->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius));
	this->eax200Height->setPosition(Vec2(112.0f, HackablePreview::PreviewRadius - 48.0f));
}
