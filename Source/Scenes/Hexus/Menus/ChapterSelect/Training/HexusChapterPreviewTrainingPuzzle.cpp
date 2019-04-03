#include "HexusChapterPreviewTrainingPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/TrainingGrounds.h"

using namespace cocos2d;

const std::string HexusChapterPreviewTrainingPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_TRAINING_PUZZLES";

HexusChapterPreviewTrainingPuzzle* HexusChapterPreviewTrainingPuzzle::create()
{
	HexusChapterPreviewTrainingPuzzle* instance = new HexusChapterPreviewTrainingPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewTrainingPuzzle::HexusChapterPreviewTrainingPuzzle() : HexusChapterPreview(HexusChapterPreviewTrainingPuzzle::SaveKeyChapterName, Strings::Menus_Maps_TrainingGrounds::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameTraining));
}

HexusChapterPreviewTrainingPuzzle::~HexusChapterPreviewTrainingPuzzle()
{
}

void HexusChapterPreviewTrainingPuzzle::initializePositions()
{
	super::initializePositions();
}
