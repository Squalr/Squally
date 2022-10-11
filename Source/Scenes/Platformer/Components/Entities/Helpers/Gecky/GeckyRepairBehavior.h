#pragma once

#include "Engine/Components/GameComponent.h"

class InteractObject;
class MinMaxPool;
class PlatformerEntity;
class Sound;

class GeckyRepairBehavior : public GameComponent
{
public:
	static GeckyRepairBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyRepairBehavior(GameObject* owner);
	virtual ~GeckyRepairBehavior();

	void onLoad() override;
	void update(float dt) override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void tryRepair(InteractObject* target, std::function<void()> onRepaired, std::string repairEvent, std::string repairSaveKey);
	void endRepair();

	PlatformerEntity* entity = nullptr;
	InteractObject* target = nullptr;
	Sound* sound = nullptr;
	bool isRepairing = false;
};
