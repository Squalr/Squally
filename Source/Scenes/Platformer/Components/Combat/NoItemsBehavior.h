#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;

class NoItemsBehavior : public GameComponent
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
	typedef GameComponent super;

	void runTutorial();

	PlatformerEntity* entity = nullptr;
};
