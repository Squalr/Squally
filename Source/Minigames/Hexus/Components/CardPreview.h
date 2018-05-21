#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "MiniGames/Hexus/Components/ComponentBase.h"
#include "GUI/Components/MenuSprite.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class CardPreview : public ComponentBase
{
public:
	static CardPreview * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	CardPreview();
	~CardPreview();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void initializeCallbacks(GameState* gameState);
	void previewCard(Card* card);

	Card* currentPreviewCard;
	Node* previewPanel;
};
