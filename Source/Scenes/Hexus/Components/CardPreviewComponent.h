#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class CardPreview;

class CardPreviewComponent : public ComponentBase
{
public:
	static CardPreviewComponent* create();

protected:
	void onBeforeStateChange(GameState* gameState) override;
	void onAnyStateChange(GameState* gameState) override;

private:
	typedef ComponentBase super;
	CardPreviewComponent();
	~CardPreviewComponent();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);

	CardPreview* cardPreview;
};
