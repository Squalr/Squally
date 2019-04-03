#include "HexusChapterPreviewTraining.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/TrainingGrounds.h"

using namespace cocos2d;

const std::string HexusChapterPreviewTraining::SaveKeyChapterName = "HEXUS_CHAPTER_TRAINING";

HexusChapterPreviewTraining* HexusChapterPreviewTraining::create()
{
	HexusChapterPreviewTraining* instance = new HexusChapterPreviewTraining();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewTraining::HexusChapterPreviewTraining() : HexusChapterPreview(HexusChapterPreviewTraining::SaveKeyChapterName, Strings::Menus_Maps_TrainingGrounds::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameTraining));
}

HexusChapterPreviewTraining::~HexusChapterPreviewTraining()
{
}

void HexusChapterPreviewTraining::initializePositions()
{
	super::initializePositions();
}
