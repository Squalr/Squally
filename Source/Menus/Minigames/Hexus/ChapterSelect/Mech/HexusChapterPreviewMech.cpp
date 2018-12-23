#include "HexusChapterPreviewMech.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string HexusChapterPreviewMech::SaveKeyChapterName = "HEXUS_CHAPTER_MECH";

HexusChapterPreviewMech* HexusChapterPreviewMech::create()
{
	HexusChapterPreviewMech* instance = new HexusChapterPreviewMech();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewMech::HexusChapterPreviewMech() : HexusChapterPreview(HexusChapterPreviewMech::SaveKeyChapterName)
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameMech));
	this->text->setString("Laboratory");
}

HexusChapterPreviewMech::~HexusChapterPreviewMech()
{
}

void HexusChapterPreviewMech::initializePositions()
{
	HexusChapterPreview::initializePositions();
}
