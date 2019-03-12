#include "HexusChapterPreviewBalmerPeaks.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/UIResources.h"

#include "Strings/Menus/Maps/BallmerPeaks.h"

using namespace cocos2d;

const std::string HexusChapterPreviewBalmerPeaks::SaveKeyChapterName = "HEXUS_CHAPTER_BALMER_PEAKS";

HexusChapterPreviewBalmerPeaks* HexusChapterPreviewBalmerPeaks::create()
{
	HexusChapterPreviewBalmerPeaks* instance = new HexusChapterPreviewBalmerPeaks();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewBalmerPeaks::HexusChapterPreviewBalmerPeaks() : HexusChapterPreview(HexusChapterPreviewBalmerPeaks::SaveKeyChapterName, Strings::Menus_Maps_BallmerPeaks::create())
{
	this->frameClip->addChild(Sprite::create(UIResources::Menus_MinigamesMenu_Hexus_HexusFrameIceCaps));
}

HexusChapterPreviewBalmerPeaks::~HexusChapterPreviewBalmerPeaks()
{
}

void HexusChapterPreviewBalmerPeaks::initializePositions()
{
	super::initializePositions();
}
