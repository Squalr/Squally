#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;

class ChoicesMenu : public SmartNode
{
public:
	static ChoicesMenu* create();

private:
	typedef SmartNode super;
	ChoicesMenu();
	virtual ~ChoicesMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();

	ClickableTextNode* itemsNode;
	ClickableTextNode* attackNode;
	ClickableTextNode* defendNode;

	static const float InnerChoicesRadius;
	static const float OuterChoicesRadius;
};
