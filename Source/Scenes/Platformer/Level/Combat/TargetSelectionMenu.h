#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class TargetSelectionMenu : public Hud
{
public:
	static TargetSelectionMenu* create();

private:
	typedef Hud super;
	TargetSelectionMenu();
	virtual ~TargetSelectionMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
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
