#pragma once

#include "Engine/UI/HUD/Hud.h"

class ChooseTargetMenu;
class PlatformerEntity;
class Timeline;

class TargetSelectionMenu : public Hud
{
public:
	static TargetSelectionMenu* create(Timeline* timelineRef);

	void selectEntity(PlatformerEntity* entity);

protected:
	TargetSelectionMenu(Timeline* timelineRef);
	virtual ~TargetSelectionMenu();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef Hud super;

	void switchToInputMode();
	void switchToMouseMode();
	void chooseCurrentTarget();
	void setEntityClickCallbacks();
	void setEntityClickCallbacks(PlatformerEntity* entity);
	void clearEntityClickCallbacks();
	void selectNext(bool directionIsLeft, bool withMouseHitTest);

	enum class AllowedSelection
	{
		None,
		PlayerResurrection,
		Player,
		Enemy,
		Either
	};

	AllowedSelection allowedSelection = AllowedSelection::None;
	Timeline* timelineRef = nullptr;
	PlatformerEntity* selectedEntity = nullptr;
	ChooseTargetMenu* chooseTargetMenu = nullptr;
	bool isActive = false;
	bool areCallbacksSet = false;
};
