#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class IncrementHealthFlaskTutorialBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
};
