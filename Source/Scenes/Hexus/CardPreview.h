#pragma once

#include "Engine/SmartNode.h"

class Card;

class CardPreview : public SmartNode
{
public:
	static CardPreview* create();
	
	void previewCard(Card* card);
	void clearPreview();

private:
	typedef SmartNode super;
	CardPreview();
	~CardPreview();

	void onEnter() override;

	Card* currentPreviewCard;
	cocos2d::Node* previewPanel;
};
