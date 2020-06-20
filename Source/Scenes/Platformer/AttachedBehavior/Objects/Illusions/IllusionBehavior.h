#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Portal;

class IllusionBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	Portal* portal;
	GameObject* object;
	std::string group;

	static const std::string PropertyGroup;
	static const std::string SaveKeyDispelled;
};
