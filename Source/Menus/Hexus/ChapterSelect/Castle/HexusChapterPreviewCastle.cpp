#include "HexusChapterPreviewCastle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/CastleValgrind.h"

using namespace cocos2d;

const std::string HexusChapterPreviewCastle::SaveKeyChapterName = "HEXUS_CHAPTER_CASTLE";

HexusChapterPreviewCastle* HexusChapterPreviewCastle::create()
{
	HexusChapterPreviewCastle* instance = new HexusChapterPreviewCastle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewCastle::HexusChapterPreviewCastle() : HexusChapterPreview(HexusChapterPreviewCastle::SaveKeyChapterName, Strings::Menus_Maps_CastleValgrind::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameCastle));
}

HexusChapterPreviewCastle::~HexusChapterPreviewCastle()
{
}

void HexusChapterPreviewCastle::initializePositions()
{
	super::initializePositions();
}
