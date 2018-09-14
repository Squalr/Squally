#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class ControlDraw : public ComponentBase
{
public:
	static ControlDraw * create();

protected:
	void onStateChange(GameState* gameState) override;

private:
	ControlDraw();
	~ControlDraw();

	void doInitialCardDraw(GameState* gameState);
	void doCardDraw(GameState* gameState);
};
