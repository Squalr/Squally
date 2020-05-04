#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HackableObject;
class Portal;

class DispelIllusionBehavior : public AttachedBehavior
{
public:
	static DispelIllusionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	DispelIllusionBehavior(GameObject* owner);
	virtual ~DispelIllusionBehavior();

	void onLoad() override;
	void onDisable() override;
	void registerHackables();

private:
	typedef AttachedBehavior super;

	void onDispelActivated();

	Portal* portal;
	HackableObject* object;
	std::string group;

	static const std::string PropertyGroup;
	static const std::string SaveKeyDispelled;
};
