#pragma once

#include "Engine/Components/GameComponent.h"

class MinMaxPool;
class PlatformerEntity;

class GrimSoulHarvestBehavior : public GameComponent
{
public:
	static GrimSoulHarvestBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimSoulHarvestBehavior(GameObject* owner);
	virtual ~GrimSoulHarvestBehavior();

	void onLoad() override;
	void update(float dt) override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void trySoulHarvest(PlatformerEntity* target, std::function<void()> onSoulHarvested, std::string pickPocketSaveKey);
	void endSoulHarvest();

	PlatformerEntity* entity = nullptr;
	PlatformerEntity* target = nullptr;
	bool isSoulHarvesting = false;
};
