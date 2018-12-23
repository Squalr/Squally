#include "HexusChapterPreviewTraining.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewTraining::SaveKeyChapterName = "HEXUS_CHAPTER_TRAINING";

HexusChapterPreviewTraining* HexusChapterPreviewTraining::create()
{
	HexusChapterPreviewTraining* instance = new HexusChapterPreviewTraining();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewTraining::HexusChapterPreviewTraining() : HexusChapterPreview(HexusChapterPreviewTraining::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameTraining));
	this->text->setString("Training Grounds");
}

HexusChapterPreviewTraining::~HexusChapterPreviewTraining()
{
}

void HexusChapterPreviewTraining::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
