#include "HexusChapterPreviewVoidStar.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/VoidStar.h"

using namespace cocos2d;

const std::string HexusChapterPreviewVoidStar::SaveKeyChapterName = "HEXUS_CHAPTER_VOID_STAR";

HexusChapterPreviewVoidStar* HexusChapterPreviewVoidStar::create()
{
	HexusChapterPreviewVoidStar* instance = new HexusChapterPreviewVoidStar();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewVoidStar::HexusChapterPreviewVoidStar() : HexusChapterPreview(HexusChapterPreviewVoidStar::SaveKeyChapterName, Strings::Menus_Maps_VoidStar::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameObelisk));
}

HexusChapterPreviewVoidStar::~HexusChapterPreviewVoidStar()
{
}

void HexusChapterPreviewVoidStar::initializePositions()
{
	super::initializePositions();
}
