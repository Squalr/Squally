#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusChapterPreview : public SmartNode
{
public:
	static HexusChapterPreview * create(std::string chapterNameKey);

	void setClickCallback(std::function<void()> callback);
	void disableInteraction();
	void enableInteraction();

	std::string chapterNameKey;

protected:
	HexusChapterPreview(std::string chapterNameKey);
	~HexusChapterPreview();

	void initializePositions() override;
	void initializeListeners() override;
	void onOpponentClick(MenuSprite* HexusChapterPreview);
	
	ClippingNode* frameClip;
	MenuSprite* frame;
	Label* text;
	std::function<void()> callback;
};
