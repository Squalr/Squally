#pragma once
#include "cocos2d.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/Utils/StrUtils.h"
#include "Resources.h"
#include "Scenes/Hexus/Components/ComponentBase.h"

using namespace cocos2d;

class DebugDisplay : public ComponentBase
{
public:
	static DebugDisplay* create();

protected:
	void onBeforeStateChange(GameState* eventCustom) override;
	void onAnyStateChange(GameState* eventCustom) override;

private:
	DebugDisplay();
	~DebugDisplay();

	void initializePositions() override;

	Label* stateLabel;

	static const bool enabled;
};
