#include "SpikedLogRailedSetRotationPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/EntityResources.h"
#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikedLogRailedSetRotationPreview* SpikedLogRailedSetRotationPreview::create()
{
	SpikedLogRailedSetRotationPreview* instance = new SpikedLogRailedSetRotationPreview();

	instance->autorelease();

	return instance;
}

SpikedLogRailedSetRotationPreview::SpikedLogRailedSetRotationPreview()
{
	this->previewSpikedLogRailed = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);
	this->eaxString = ConstantString::create("1");
	this->animationLength = SmartAnimationSequenceNode::GetAnimationLength(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);
	this->previewSqually = Sprite::create(EntityResources::Squally_Emblem);

	this->previewSpikedLogRailed->setScale(0.4f);
	this->eaxLabel = this->createRegisterEqualsValueLabel(HackableCode::Register::zax, false, this->eaxString);

	this->previewNode->addChild(this->previewSpikedLogRailed);
	this->previewNode->addChild(this->previewSqually);
	this->assemblyTextNode->addChild(this->eaxLabel);
}

SpikedLogRailedSetRotationPreview::~SpikedLogRailedSetRotationPreview()
{
}

HackablePreview* SpikedLogRailedSetRotationPreview::clone()
{
	return SpikedLogRailedSetRotationPreview::create();
}

void SpikedLogRailedSetRotationPreview::onEnter()
{
	super::onEnter();
	
	const float speed = 1.5f;
	const float range = HackablePreview::PreviewRadius - 72.0f;

	this->previewSpikedLogRailed->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLogRailed->playAnimationRepeat(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00, 0.08f, 0.0f);
	this->previewSqually->setFlippedX(true);

	this->previewSqually->setPositionY(-72.0f);

	this->previewSqually->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-range, this->previewSqually->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(range, this->previewSqually->getPositionY()))),
			nullptr
		))
	);
	this->previewSpikedLogRailed->runAction(
		RepeatForever::create(Sequence::create(
			EaseSineInOut::create(MoveTo::create(speed, Vec2(range, this->previewSpikedLogRailed->getPositionY()))),
			EaseSineInOut::create(MoveTo::create(speed, Vec2(-range, this->previewSpikedLogRailed->getPositionY()))),
			nullptr
		))
	);
	this->runAction(
		RepeatForever::create(Sequence::create(
			DelayTime::create(speed),
			CallFunc::create([=]()
			{
				this->previewSqually->setFlippedX(false);
				this->eaxString->setString("-1");
			}),
			DelayTime::create(speed),
			CallFunc::create([=]()
			{
				this->previewSqually->setFlippedX(true);
				this->eaxString->setString("1");
			}),
			nullptr
		))
	);
}

void SpikedLogRailedSetRotationPreview::initializePositions()
{
	super::initializePositions();

	this->eaxLabel->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 32.0f));
}
