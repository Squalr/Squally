#include "HexusChapterPreviewVoidStar.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

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
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameVoidStar));
}

HexusChapterPreviewVoidStar::~HexusChapterPreviewVoidStar()
{
}

void HexusChapterPreviewVoidStar::initializePositions()
{
	super::initializePositions();
}
