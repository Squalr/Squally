#include "CatapultApplyPowerPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CatapultApplyPowerPreview* CatapultApplyPowerPreview::create()
{
	CatapultApplyPowerPreview* instance = new CatapultApplyPowerPreview();

	instance->autorelease();

	return instance;
}

CatapultApplyPowerPreview::CatapultApplyPowerPreview()
{
	this->catapultBall1 = Sprite::create(ObjectResources::Traps_Catapult_BALL);
	this->catapultBall2 = Sprite::create(ObjectResources::Traps_Catapult_BALL);

	this->xmm1Low = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("0.5f"));
	this->xmm1High = this->createRegisterEqualsValueLabel(HackableCode::Register::xmm1, false, ConstantString::create("1.0f"));

	this->catapultBall1->setScale(0.35f);
	this->catapultBall2->setScale(0.35f);

	this->previewNode->addChild(this->catapultBall1);
	this->previewNode->addChild(this->catapultBall2);
	this->assemblyTextNode->addChild(this->xmm1Low);
	this->assemblyTextNode->addChild(this->xmm1High);
}

HackablePreview* CatapultApplyPowerPreview::clone()
{
	return CatapultApplyPowerPreview::create();
}

void CatapultApplyPowerPreview::onEnter()
{
	super::onEnter();

	const float speed = 0.75f;

	this->catapultBall1->setPosition(Vec2(-HackablePreview::PreviewRadius + 64.0f, 80.0f));
	this->catapultBall2->setPosition(Vec2(-HackablePreview::PreviewRadius + 16.0f, -32.0f));

	Vec2 catapultBall1Spawn = this->catapultBall1->getPosition();
	Vec2 catapultBall2Spawn = this->catapultBall2->getPosition();

	this->catapultBall1->runAction(
		RepeatForever::create(Sequence::create(
			FadeTo::create(0.25f, 255),
			Spawn::createWithTwoActions(
				MoveBy::create(speed, Vec2(128.0f, 0.0f)),
				EaseSineIn::create(MoveBy::create(speed, Vec2(0.0f, -48.0f)))
			),
			FadeTo::create(0.25f, 0),
			MoveTo::create(0.0f, catapultBall1Spawn),
			DelayTime::create(0.25f),
			nullptr
		))
	);

	this->catapultBall2->runAction(
		RepeatForever::create(Sequence::create(
			FadeTo::create(0.25f, 255),
			Spawn::createWithTwoActions(
				MoveBy::create(speed, Vec2(256.0f, 0.0f)),
				EaseSineIn::create(MoveBy::create(speed, Vec2(0.0f, -48.0f)))
			),
			FadeTo::create(0.25f, 0),
			MoveTo::create(0.0f, catapultBall2Spawn),
			DelayTime::create(0.25f),
			nullptr
		))
	);
}

void CatapultApplyPowerPreview::initializePositions()
{
	super::initializePositions();

	const float offset = 32.0f;

	this->xmm1Low->setPosition(Vec2(0.0f, 0.0f));
	this->xmm1High->setPosition(Vec2(0.0f, -HackablePreview::PreviewRadius + offset));
}
