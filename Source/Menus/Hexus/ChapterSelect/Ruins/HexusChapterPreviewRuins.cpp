#include "HexusChapterPreviewRuins.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/UnderflowRuins.h"

using namespace cocos2d;

const std::string HexusChapterPreviewRuins::SaveKeyChapterName = "HEXUS_CHAPTER_RUINS";

HexusChapterPreviewRuins* HexusChapterPreviewRuins::create()
{
	HexusChapterPreviewRuins* instance = new HexusChapterPreviewRuins();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewRuins::HexusChapterPreviewRuins() : HexusChapterPreview(HexusChapterPreviewRuins::SaveKeyChapterName, LocaleStrings::UnderflowRuins::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
}

HexusChapterPreviewRuins::~HexusChapterPreviewRuins()
{
}

void HexusChapterPreviewRuins::initializePositions()
{
	super::initializePositions();
}
