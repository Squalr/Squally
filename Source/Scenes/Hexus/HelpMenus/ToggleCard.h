#pragma once

#include "Engine/SmartNode.h"
#include "Scenes/Hexus/HelpMenus/AutoCard.h"

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

	void setToggleAttackCallback(std::function<void()> onToggleAttackChange);
	void setToggleDisplayTypeCallback(std::function<void()> onToggleDisplayTypeChange);
	void toggleNextValue();
	void togglePreviousValue();
	void setDisplayType(AutoCard::DisplayType displayType, bool triggerCallback = true);
	void toggleNextDisplayType();
	void togglePreviousDisplayType();
	void setAttack(int attack);
	int getAttack();
	void setCardScale(float cardScale);

	AutoCard* autoCard;

protected:
	ToggleCard(ToggleModeLeftRight toggleModeLeftRight, ToggleModeUpDown toggleModeUpDown);
	virtual ~ToggleCard();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

private:
	typedef SmartNode super;

	void updateUpDownDisplays();

	ToggleModeLeftRight toggleModeLeftRight;
	ToggleModeUpDown toggleModeUpDown;

	ClickableNode* upToggle;
	ClickableNode* downToggle;
	ClickableNode* leftToggle;
	ClickableNode* rightToggle;
	std::function<void()> onToggleAttackChange;
	std::function<void()> onToggleDisplayTypeChange;
};
