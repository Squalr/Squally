#pragma once

#include "Engine/SmartNode.h"

class AutoCard;
class ClickableNode;

class ToggleCard : public SmartNode
{
public:
	enum class ToggleMode
	{
		Hidden,
		LeftRight,
		UpDown,
	};

	static ToggleCard* create(ToggleMode toggleMode);

	void setToggleCallback(std::function<void()> onToggleChange);
	void toggleNext();
	void togglePrevious();

	AutoCard* autoCard;

private:
	typedef SmartNode super;
	ToggleCard(ToggleMode toggleMode);
	~ToggleCard();

	void onEnter() override;
	void initializeListeners() override;
	void initializePositions() override;

	ClickableNode* upToggle;
	ClickableNode* downToggle;
	ClickableNode* leftToggle;
	ClickableNode* rightToggle;
	std::function<void()> onToggleChange;
};
