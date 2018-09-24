#pragma once
#include "cocos2d.h"
#include "Resources.h"

#include "Engine/SmartNode.h"
#include "Events/HexusEvents.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class HexusChapterPreview : public SmartNode
{
public:
	static HexusChapterPreview * create();

	void setClickCallback(std::function<void()> callback);

protected:
	HexusChapterPreview();
	~HexusChapterPreview();

	void initializePositions() override;
	void initializeListeners() override;
	void onOpponentClick(MenuSprite* HexusChapterPreview);
	void onOpponentMouseOver(MenuSprite* HexusChapterPreview);
	
	ClippingNode* frameClip;
	MenuSprite* frame;
	std::function<void()> callback;
};
