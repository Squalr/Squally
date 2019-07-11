#include "HexusChapterPreviewUnderflowRuins.h"

#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

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
	this->contentNode->addChild(Sprite::create(HexusResources::Menus_HexusFrameUnderflowRuins));
}

HexusChapterPreviewUnderflowRuins::~HexusChapterPreviewUnderflowRuins()
{
}

void HexusChapterPreviewUnderflowRuins::initializePositions()
{
	super::initializePositions();
}
