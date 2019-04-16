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

private:
	typedef SmartNode super;
	CardPreview();
	~CardPreview();

	void onEnter() override;
	void initializePositions() override;

	cocos2d::Sprite* cardPad;
	Card* currentPreviewCard;
	cocos2d::Node* previewPanel;
	ClickableTextNode* helpButton;
	
	std::function<void(Card* card)> onHelpClick;
};
