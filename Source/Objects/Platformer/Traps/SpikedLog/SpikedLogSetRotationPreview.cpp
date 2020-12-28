#include "SpikedLogSetRotationPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikedLogSetRotationPreview* SpikedLogSetRotationPreview::create()
{
	SpikedLogSetRotationPreview* instance = new SpikedLogSetRotationPreview();

	instance->autorelease();

	return instance;
}

SpikedLogSetRotationPreview::SpikedLogSetRotationPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikedLog_SpikedLog_00);
	this->countString = ConstantString::create("0");
	this->currentAnimationIndex = -1;
	this->animationLength = SmartAnimationSequenceNode::GetAnimationLength(ObjectResources::Traps_SpikedLog_SpikedLog_00);

	this->previewSpikedLog->setScale(0.4f);
	this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, this->countString);

	this->previewNode->addChild(this->previewSpikedLog);
	this->assemblyTextNode->addChild(this->ecxAnimationCount);
}

SpikedLogSetRotationPreview::~SpikedLogSetRotationPreview()
{
}

HackablePreview* SpikedLogSetRotationPreview::clone()
{
	return SpikedLogSetRotationPreview::create();
}

void SpikedLogSetRotationPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));

	this->onFrameComplete();
}

void SpikedLogSetRotationPreview::onFrameComplete()
{
	this->currentAnimationIndex = MathUtils::wrappingNormalize(this->currentAnimationIndex + 1, 0, this->animationLength - 1);
	this->countString->setString(std::to_string(this->currentAnimationIndex));

	this->previewSpikedLog->playSingleFrame(ObjectResources::Traps_SpikedLog_SpikedLog_00, this->currentAnimationIndex, 0.5f, [=]()
	{
		this->onFrameComplete();
	});
}

void SpikedLogSetRotationPreview::initializePositions()
{
	super::initializePositions();

	this->ecxAnimationCount->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 64.0f));
}
