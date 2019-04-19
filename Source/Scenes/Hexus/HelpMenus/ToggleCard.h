#pragma once

#include "Engine/SmartNode.h"

class AutoCard;
class ClickableNode;

class ToggleCard : public SmartNode
{
public:
	enum class ToggleModeLeftRight
	{
		Hidden,
		LeftRight,
	};

	enum class ToggleModeUpDown
	{
		Hidden,
		BinDec,
		DecHex,
		HexBin,
		BinDecHex,
	};

	static ToggleCard* create(ToggleModeLeftRight toggleModeLeftRight, ToggleModeUpDown toggleModeUpDown = ToggleModeUpDown::Hidden);

	void setToggleCallback(std::function<void()> onToggleChange);
	void toggleNextValue();
	void togglePreviousValue();
	void toggleNextDisplayType();
	void togglePreviousDisplayType();

	AutoCard* autoCard;

private:
	typedef SmartNode super;
	ToggleCard(ToggleModeLeftRight toggleModeLeftRight, ToggleModeUpDown toggleModeUpDown);
	~ToggleCard();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	void updateUpDownDisplays();

	ToggleModeLeftRight toggleModeLeftRight;
	ToggleModeUpDown toggleModeUpDown;

	ClickableNode* upToggleBin;
	ClickableNode* upToggleDec;
	ClickableNode* upToggleHex;
	ClickableNode* downToggleBin;
	ClickableNode* downToggleDec;
	ClickableNode* downToggleHex;

	ClickableNode* leftToggle;
	ClickableNode* rightToggle;
	std::function<void()> onToggleChange;
};
