#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class IncrementHealthFlaskTutorialBehavior : public GameComponent
{
public:
	static IncrementHealthFlaskTutorialBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	IncrementHealthFlaskTutorialBehavior(GameObject* owner);
	virtual ~IncrementHealthFlaskTutorialBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;
};
