#include "HexusChapterPreviewBalmerPeaks.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

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
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameBalmerPeaks));
}

HexusChapterPreviewBalmerPeaks::~HexusChapterPreviewBalmerPeaks()
{
}

void HexusChapterPreviewBalmerPeaks::initializePositions()
{
	super::initializePositions();
}
