#pragma once
#include "cocos2d.h"

#include "Engine/Localization/Localization.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class RowTotals : public ComponentBase
{
public:
	static RowTotals * create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onStateChange(GameState* eventCustom) override;

private:
	RowTotals();
	~RowTotals();

	void initializePositions() override;
	void updateTotals(GameState* gameState);

	Label* enemyBinaryCardTotal;
	Label* enemyDecimalCardTotal;
	Label* enemyHexCardTotal;
	Label* playerBinaryCardTotal;
	Label* playerDecimalCardTotal;
	Label* playerHexCardTotal;
};
