#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class Card;
class ClickableTextNode;

class CardPreview : public SmartNode
{
public:
	static CardPreview* create();
	
	void previewCard(Card* card);
	void clearPreview();
	void setHelpClickCallback(std::function<void(Card* card)> onHelpClick);

protected:
	CardPreview();
	virtual ~CardPreview();
	
	void onEnter() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	struct PreviewData
	{
		Card* previewCard;
		cocos2d::Node* previewNode;

		PreviewData() : previewCard(nullptr), previewNode(nullptr) { }
		PreviewData(Card* previewCard, cocos2d::Node* previewNode) : previewCard(previewCard), previewNode(previewNode) { }
	};

	CardPreview::PreviewData constructPreview(Card* card);

	cocos2d::Sprite* cardPad;
	PreviewData currentPreviewData;
	cocos2d::Node* previewPanel;
	ClickableTextNode* helpButton;
	
	std::function<void(Card* card)> onHelpClick;
	std::map<std::string, PreviewData> previewCache;
};
