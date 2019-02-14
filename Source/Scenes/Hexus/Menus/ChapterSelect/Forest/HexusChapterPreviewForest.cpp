#include "HexusChapterPreviewForest.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/EndianForest.h"

using namespace cocos2d;

const std::string HexusChapterPreviewForest::SaveKeyChapterName = "HEXUS_CHAPTER_FOREST";

HexusChapterPreviewForest* HexusChapterPreviewForest::create()
{
	HexusChapterPreviewForest* instance = new HexusChapterPreviewForest();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewForest::HexusChapterPreviewForest() : HexusChapterPreview(HexusChapterPreviewForest::SaveKeyChapterName, Strings::Menus_Maps_EndianForest::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest));
}

HexusChapterPreviewForest::~HexusChapterPreviewForest()
{
}

void HexusChapterPreviewForest::initializePositions()
{
	super::initializePositions();
}
