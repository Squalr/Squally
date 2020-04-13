#include "SpikeLogSetRotationPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/MathUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

SpikeLogSetRotationPreview* SpikeLogSetRotationPreview::create()
{
	SpikeLogSetRotationPreview* instance = new SpikeLogSetRotationPreview();

	instance->autorelease();

	return instance;
}

SpikeLogSetRotationPreview::SpikeLogSetRotationPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLog_SpikedLog_00);

	this->previewSpikedLog->setScale(0.4f);

	this->countString = ConstantString::create("0");

	this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, this->countString);

	this->previewNode->addChild(this->previewSpikedLog);
	this->assemblyTextNode->addChild(this->ecxAnimationCount);
}

HackablePreview* SpikeLogSetRotationPreview::clone()
{
	return SpikeLogSetRotationPreview::create();
}

void SpikeLogSetRotationPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLog_SpikedLog_00, 0.5f, 0.0f);

	this->previewSpikedLog->getForwardsAnimation()->incrementCallback = [=](int count, int max)
	{
		count = MathUtils::wrappingNormalize(count + 1, 0, max);

		this->countString->setString(std::to_string(count));

		return count;
	};
}

void SpikeLogSetRotationPreview::initializePositions()
{
	super::initializePositions();

	this->ecxAnimationCount->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 64.0f));
}
