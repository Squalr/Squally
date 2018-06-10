#pragma once
#include "cocos2d.h"


#include "Engine/Rendering/Components/MenuSprite.h"
#include "Resources.h"
#include "Utils/StrUtils.h"

#include "ComponentBase.h"

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

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
	void doInitialCardDraw(GameState* gameState);
	void doCardDraw(GameState* gameState);
};
