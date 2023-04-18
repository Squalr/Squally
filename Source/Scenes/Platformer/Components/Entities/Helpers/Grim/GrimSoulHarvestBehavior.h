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

	void tryPickPocket(PlatformerEntity* target, MinMaxPool* pocketPool, std::function<void()> onPickPocket, std::string pickPocketSaveKey);
	void endPickPocket();

	PlatformerEntity* entity = nullptr;
	PlatformerEntity* target = nullptr;
	bool isPickPocketing = false;
};
