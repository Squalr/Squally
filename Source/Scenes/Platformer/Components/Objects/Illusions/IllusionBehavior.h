#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Portal;

class IllusionBehavior : public GameComponent
{
public:
	static IllusionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	IllusionBehavior(GameObject* owner);
	virtual ~IllusionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Portal* portal = nullptr;
	PlatformerEntity* entity = nullptr;
	GameObject* object = nullptr;
	std::string group;

	static const std::string PropertyGroup;
	static const std::string SaveKeyDispelled;
};
