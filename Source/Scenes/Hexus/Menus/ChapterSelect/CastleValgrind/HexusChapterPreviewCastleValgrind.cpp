#include "HexusChapterPreviewCastleValgrind.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/CastleValgrind.h"

using namespace cocos2d;

const std::string HexusChapterPreviewCastleValgrind::SaveKeyChapterName = "HEXUS_CHAPTER_CASTLE_VALGRIND";

HexusChapterPreviewCastleValgrind* HexusChapterPreviewCastleValgrind::create()
{
	HexusChapterPreviewCastleValgrind* instance = new HexusChapterPreviewCastleValgrind();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCastleValgrind::HexusChapterPreviewCastleValgrind() : HexusChapterPreview(HexusChapterPreviewCastleValgrind::SaveKeyChapterName, Strings::Menus_Maps_CastleValgrind::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_Hexus_HexusFrameCastleValgrind));
}

HexusChapterPreviewCastleValgrind::~HexusChapterPreviewCastleValgrind()
{
}

void HexusChapterPreviewCastleValgrind::initializePositions()
{
	super::initializePositions();
}
