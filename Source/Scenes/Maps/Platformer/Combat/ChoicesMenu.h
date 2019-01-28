#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableNode;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create(std::function<void()> onChoiceMadeCallback);

private:
	typedef SmartNode super;
	ChoicesMenu(std::function<void()> onChoiceMadeCallback);
	virtual ~ChoicesMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();

	ClickableNode* itemsNode;
	ClickableNode* attackNode;
	ClickableNode* defendNode;
	std::function<void()> onChoiceMadeCallback;

	static const float InnerChoicesRadius;
	static const float OuterChoicesRadius;
};
