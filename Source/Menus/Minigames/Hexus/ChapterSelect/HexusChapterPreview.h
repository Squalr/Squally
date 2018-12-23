#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
}

class LocalizedLabel;
class MenuSprite;
class LocalizedLabel;

class HexusChapterPreview : public SmartNode
{
public:
	static HexusChapterPreview* create(std::string chapterNameKey);

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
	
	cocos2d::ClippingNode* frameClip;
	MenuSprite* frame;
	LocalizedLabel* text;
	std::function<void()> callback;
};
