#pragma once

#include "Engine/Components/GameComponent.h"

class MinMaxPool;
class PlatformerEntity;

class GuanoPickPocketBehavior : public GameComponent
{
public:
	static GuanoPickPocketBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoPickPocketBehavior(GameObject* owner);
	virtual ~GuanoPickPocketBehavior();

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
