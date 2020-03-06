#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Portal;

class DispelIllusionBehavior : public AttachedBehavior
{
public:
	static DispelIllusionBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	DispelIllusionBehavior(GameObject* owner);
	virtual ~DispelIllusionBehavior();

	void onLoad() override;
	void registerHackables() override;

private:
	typedef AttachedBehavior super;

	void onDispelActivated();

	Portal* portal;
	GameObject* object;
	std::string group;

	static const std::string MapPropertyGroup;
};
