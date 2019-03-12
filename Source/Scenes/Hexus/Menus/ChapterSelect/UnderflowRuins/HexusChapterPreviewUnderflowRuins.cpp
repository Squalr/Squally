#include "HexusChapterPreviewUnderflowRuins.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/UnderflowRuins.h"

using namespace cocos2d;

const std::string HexusChapterPreviewUnderflowRuins::SaveKeyChapterName = "HEXUS_CHAPTER_UNDERFLOW_RUINS";

HexusChapterPreviewUnderflowRuins* HexusChapterPreviewUnderflowRuins::create()
{
	HexusChapterPreviewUnderflowRuins* instance = new HexusChapterPreviewUnderflowRuins();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewUnderflowRuins::HexusChapterPreviewUnderflowRuins() : HexusChapterPreview(HexusChapterPreviewUnderflowRuins::SaveKeyChapterName, Strings::Menus_Maps_UnderflowRuins::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameRuins));
}

HexusChapterPreviewUnderflowRuins::~HexusChapterPreviewUnderflowRuins()
{
}

void HexusChapterPreviewUnderflowRuins::initializePositions()
{
	super::initializePositions();
}
