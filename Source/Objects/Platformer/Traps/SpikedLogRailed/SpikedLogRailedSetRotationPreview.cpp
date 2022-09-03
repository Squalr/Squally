#include "SpikedLogRailedSetRotationPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

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
	this->countString = ConstantString::create("0");
	this->animationLength = SmartAnimationSequenceNode::GetAnimationLength(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00);

	this->previewSpikedLogRailed->setScale(0.4f);
	this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, this->countString);

	this->previewNode->addChild(this->previewSpikedLogRailed);
	this->assemblyTextNode->addChild(this->ecxAnimationCount);
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

	this->previewSpikedLogRailed->setPosition(Vec2(0.0f, 0.0f));

	this->onFrameComplete();
}

void SpikedLogRailedSetRotationPreview::onFrameComplete()
{
	this->currentAnimationIndex = MathUtils::wrappingNormalize(this->currentAnimationIndex + 1, 0, this->animationLength - 1);
	this->countString->setString(std::to_string(this->currentAnimationIndex));

	this->previewSpikedLogRailed->playSingleFrame(ObjectResources::Traps_SpikedLogRailed_SpikedLog_00, this->currentAnimationIndex, 0.5f, [=]()
	{
		this->onFrameComplete();
	});
}

void SpikedLogRailedSetRotationPreview::initializePositions()
{
	super::initializePositions();

	this->ecxAnimationCount->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 64.0f));
}
