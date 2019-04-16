#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class Card;
class CardPreview;

class CardPreviewComponent : public ComponentBase
{
public:
	static CardPreviewComponent* create();
	
	void setHelpClickCallback(std::function<void(Card* card)> onHelpClick);

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	CardPreviewComponent();
	~CardPreviewComponent();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void onPreviewCard(Card* card);
	void onPreviewCardBroadcast(Card* card);
	void onCardMouseOut(Card* card);

	CardPreview* cardPreview;
};
