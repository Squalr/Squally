#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

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
	Node* previewPanel;
};
