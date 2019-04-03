#include "HexusChapterPreviewUnderflowRuinsPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/UnderflowRuins.h"

using namespace cocos2d;

const std::string HexusChapterPreviewUnderflowRuinsPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_UNDERFLOW_RUINS_PUZZLES";

HexusChapterPreviewUnderflowRuinsPuzzle* HexusChapterPreviewUnderflowRuinsPuzzle::create()
{
	HexusChapterPreviewUnderflowRuinsPuzzle* instance = new HexusChapterPreviewUnderflowRuinsPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewUnderflowRuinsPuzzle::HexusChapterPreviewUnderflowRuinsPuzzle() : HexusChapterPreview(HexusChapterPreviewUnderflowRuinsPuzzle::SaveKeyChapterName, Strings::Menus_Maps_UnderflowRuins::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameUnderflowRuins));
}

HexusChapterPreviewUnderflowRuinsPuzzle::~HexusChapterPreviewUnderflowRuinsPuzzle()
{
}

void HexusChapterPreviewUnderflowRuinsPuzzle::initializePositions()
{
	super::initializePositions();
}
