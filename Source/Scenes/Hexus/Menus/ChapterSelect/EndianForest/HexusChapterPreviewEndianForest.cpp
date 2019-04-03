#include "HexusChapterPreviewEndianForest.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/EndianForest.h"

using namespace cocos2d;

const std::string HexusChapterPreviewEndianForest::SaveKeyChapterName = "HEXUS_CHAPTER_ENDIAN_FOREST";

HexusChapterPreviewEndianForest* HexusChapterPreviewEndianForest::create()
{
	HexusChapterPreviewEndianForest* instance = new HexusChapterPreviewEndianForest();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewEndianForest::HexusChapterPreviewEndianForest() : HexusChapterPreview(HexusChapterPreviewEndianForest::SaveKeyChapterName, Strings::Menus_Maps_EndianForest::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameEndianForest));
}

HexusChapterPreviewEndianForest::~HexusChapterPreviewEndianForest()
{
}

void HexusChapterPreviewEndianForest::initializePositions()
{
	super::initializePositions();
}
