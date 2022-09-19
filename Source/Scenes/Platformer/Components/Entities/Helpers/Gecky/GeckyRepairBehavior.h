#pragma once

#include "Engine/Components/GameComponent.h"

class MinMaxPool;
class PlatformerEntity;

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

	void tryRepair(GameObject* target, std::string repairEvent, std::string repairSaveKey);
	void endRepair();

	PlatformerEntity* entity = nullptr;
	GameObject* target = nullptr;
	bool isRepairing = false;
};
