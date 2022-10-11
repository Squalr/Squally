#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class WorldSound;

class GuanoUnpetrifySoundBehavior : public GameComponent
{
public:
	static GuanoUnpetrifySoundBehavior* create(GameObject* owner);

	void unpetrify();

protected:
	GuanoUnpetrifySoundBehavior(GameObject* owner);
	virtual ~GuanoUnpetrifySoundBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	WorldSound* statueBreakSound = nullptr;
};
