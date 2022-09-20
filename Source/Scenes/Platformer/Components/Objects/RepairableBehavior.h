#pragma once

#include "Engine/Components/GameComponent.h"

namespace cocos2d
{
	class Sprite;
}

class InteractObject;
class Squally;

class RepairableBehavior : public GameComponent
{
public:
	static RepairableBehavior* create(GameObject* owner);
	
	bool canRepair();
	bool wasRepaired();

	static const std::string MapKey;

protected:
	RepairableBehavior(GameObject* owner);
	virtual ~RepairableBehavior();

	void initializePositions() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void attemptRepair();
	void onRepaired();
	void updateIconVisibility();
	void refreshCursorState();

	InteractObject* interactObject = nullptr;
	Squally* squally = nullptr;
	cocos2d::Sprite* repairIcon = nullptr;
	std::string repairEvent;

	std::string currentHelperName;

	static const std::string SavePropertyKeyWasRepaired;
	static const std::string MapKeyRepairEvent;
};
