#include "CrystalPuzzleIncrementPreview.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

CrystalPuzzleIncrementPreview* CrystalPuzzleIncrementPreview::create()
{
	CrystalPuzzleIncrementPreview* instance = new CrystalPuzzleIncrementPreview();

	instance->autorelease();

	return instance;
}

CrystalPuzzleIncrementPreview::CrystalPuzzleIncrementPreview()
{
	this->previewSpikedLog = SmartAnimationSequenceNode::create(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01);

	this->previewSpikedLog->setScale(0.4f);

	this->countString = ConstantString::create("0");

	this->ecxAnimationCount = this->createRegisterEqualsValueLabel(HackableCode::Register::zcx, false, this->countString);

	this->previewNode->addChild(this->previewSpikedLog);
	this->assemblyTextNode->addChild(this->ecxAnimationCount);
}

HackablePreview* CrystalPuzzleIncrementPreview::clone()
{
	return CrystalPuzzleIncrementPreview::create();
}

void CrystalPuzzleIncrementPreview::onEnter()
{
	super::onEnter();

	this->previewSpikedLog->setPosition(Vec2(0.0f, 0.0f));
	this->previewSpikedLog->playAnimationRepeat(ObjectResources::Traps_SpikeLogAvoidable_SpikedLog_01, 0.5f, 0.0f);

	this->previewSpikedLog->getForwardsAnimation()->incrementCallback = [=](int count, int max, std::string spriteResource)
	{
		this->countString->setString(std::to_string(count));

		return ++count;
	};
}

void CrystalPuzzleIncrementPreview::initializePositions()
{
	super::initializePositions();

	this->ecxAnimationCount->setPosition(Vec2(0.0f, HackablePreview::PreviewRadius - 64.0f));
}
