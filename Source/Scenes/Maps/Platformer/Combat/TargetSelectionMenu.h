#pragma once

#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class TargetSelectionMenu : public SmartNode
{
public:
	static TargetSelectionMenu* create();

private:
	typedef SmartNode super;
	TargetSelectionMenu();
	virtual ~TargetSelectionMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void selectEntity(PlatformerEntity* entity);
	void setEntityClickCallbacks();
	void clearEntityClickCallbacks();
	void selectNext(bool directionIsLeft);

	enum class AllowedSelection
	{
		Player,
		Enemy,
		Either
	};

	AllowedSelection allowedSelection;
	bool isActive;
	PlatformerEntity* selectedEntity;
	cocos2d::Sprite* lightRay;
};
