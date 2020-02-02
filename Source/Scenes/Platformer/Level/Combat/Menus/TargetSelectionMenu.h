#pragma once

#include "Engine/UI/HUD/Hud.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;
class Timeline;

class TargetSelectionMenu : public Hud
{
public:
	static TargetSelectionMenu* create(Timeline* timelineRef);

protected:
	TargetSelectionMenu(Timeline* timelineRef);
	virtual ~TargetSelectionMenu() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

private:
	typedef Hud super;
	void chooseCurrentTarget();
	void selectEntity(PlatformerEntity* entity);
	void setEntityClickCallbacks();
	void setEntityClickCallbacks(PlatformerEntity* entity);
	void clearEntityClickCallbacks();
	void selectNext(bool directionIsLeft);

	enum class AllowedSelection
	{
		Player,
		Enemy,
		Either
	};

	Timeline* timelineRef;
	AllowedSelection allowedSelection;
	bool isActive;
	PlatformerEntity* selectedEntity;
	cocos2d::Sprite* lightRay;
};
