#include "HexusChapterPreviewDaemonsHallow.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/DaemonsHallow.h"

using namespace cocos2d;

const std::string HexusChapterPreviewDaemonsHallow::SaveKeyChapterName = "HEXUS_CHAPTER_DAEMONS_HALLOW";

HexusChapterPreviewDaemonsHallow* HexusChapterPreviewDaemonsHallow::create()
{
	HexusChapterPreviewDaemonsHallow* instance = new HexusChapterPreviewDaemonsHallow();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewDaemonsHallow::HexusChapterPreviewDaemonsHallow() : HexusChapterPreview(HexusChapterPreviewDaemonsHallow::SaveKeyChapterName, Strings::Menus_Maps_DaemonsHallow::create())
{
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameDaemonsHallow));
}

HexusChapterPreviewDaemonsHallow::~HexusChapterPreviewDaemonsHallow()
{
}

void HexusChapterPreviewDaemonsHallow::initializePositions()
{
	super::initializePositions();
}
