#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class ClickableTextNode;
class PlatformerEntity;

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
	void open();
	void onUserActionMade();
	void onItemsClick();
	void onAttackClick();
	void onDefendClick();
	void toggleInnerText(bool isVisible);
	void setSelectedEntity(PlatformerEntity* selectedEntity);

	ClickableTextNode* itemsNode;
	ClickableTextNode* attackNode;
	ClickableTextNode* defendNode;
	cocos2d::Node* attackListNode;
	PlatformerEntity* selectedEntity;

	static const float InnerChoicesRadius;
	static const float OuterChoicesRadius;
};
