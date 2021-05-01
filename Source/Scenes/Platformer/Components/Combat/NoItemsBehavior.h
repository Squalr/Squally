#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;

class NoItemsBehavior : public Component
{
public:
	static NoItemsBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	NoItemsBehavior(GameObject* owner);
	virtual ~NoItemsBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void runTutorial();

	PlatformerEntity* entity;
};
