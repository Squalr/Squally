#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"

class GameState;
class LocalizedLabel;

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

	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;
	void initializePositions() override;

	LocalizedLabel* stateLabel;

	static const bool enabled;
};
