#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/States/StateBase.h"

using namespace cocos2d;

class StateDraw : public StateBase
{
public:
	static StateDraw * create();

protected:
	void beforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateDraw();
	~StateDraw();
};
