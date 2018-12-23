#include "HexusChapterPreviewForest.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewForest::SaveKeyChapterName = "HEXUS_CHAPTER_FOREST";

HexusChapterPreviewForest* HexusChapterPreviewForest::create()
{
	HexusChapterPreviewForest* instance = new HexusChapterPreviewForest();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewForest::HexusChapterPreviewForest() : HexusChapterPreview(HexusChapterPreviewForest::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameForest));
	this->text->setString("Forest");
}

HexusChapterPreviewForest::~HexusChapterPreviewForest()
{
}

void HexusChapterPreviewForest::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
