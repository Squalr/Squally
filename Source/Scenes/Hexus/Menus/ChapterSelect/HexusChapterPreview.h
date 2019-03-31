#pragma once
#include <functional>

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class ClippingNode;
}

class LocalizedLabel;
class LocalizedString;
class ClickableNode;
class LocalizedLabel;

class HexusChapterPreview : public SmartNode
{
public:
	static HexusChapterPreview* create(std::string chapterSaveKey, LocalizedString* localizedChapterName);

	void setMouseClickCallback(std::function<void()> callback);
	void disableInteraction();
	void enableInteraction();

	std::string chapterSaveKey;

protected:
	HexusChapterPreview(std::string chapterNameKey, LocalizedString* localizedChapterName);
	~HexusChapterPreview();

	void initializePositions() override;
	void initializeListeners() override;
	void onOpponentClick();
	
	cocos2d::ClippingNode* frameClip;
	ClickableNode* frame;
	LocalizedLabel* text;
	std::function<void()> callback;

private:
	typedef SmartNode super;
};
