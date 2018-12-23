#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class Card;

class CardPreview : public ComponentBase
{
public:
	static CardPreview * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	CardPreview();
	~CardPreview();

	void onEnter() override;
	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void clearPreview();
	void previewCard(Card* card);

	Card* currentPreviewCard;
	cocos2d::Node* previewPanel;
};
