#include "HexusChapterPreviewLambdaCryptsPuzzle.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Localization/LocalizedLabel.h"

#include "Resources/HexusResources.h"

#include "Strings/Menus/Maps/LambdaCrypts.h"

using namespace cocos2d;

const std::string HexusChapterPreviewLambdaCryptsPuzzle::SaveKeyChapterName = "HEXUS_CHAPTER_LAMBDA_CRYPTS_PUZZLES";

HexusChapterPreviewLambdaCryptsPuzzle* HexusChapterPreviewLambdaCryptsPuzzle::create()
{
	HexusChapterPreviewLambdaCryptsPuzzle* instance = new HexusChapterPreviewLambdaCryptsPuzzle();

	instance->autorelease();

	return instance;
}

HexusChapterPreviewLambdaCryptsPuzzle::HexusChapterPreviewLambdaCryptsPuzzle() : HexusChapterPreview(HexusChapterPreviewLambdaCryptsPuzzle::SaveKeyChapterName, Strings::Menus_Maps_LambdaCrypts::create())
{
	this->frameClip->addChild(Sprite::create(HexusResources::Menus_HexusFrameLambdaCrypts));
}

HexusChapterPreviewLambdaCryptsPuzzle::~HexusChapterPreviewLambdaCryptsPuzzle()
{
}

void HexusChapterPreviewLambdaCryptsPuzzle::initializePositions()
{
	super::initializePositions();
}
