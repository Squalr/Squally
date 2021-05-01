#pragma once

#include "Engine/Components/Component.h"

class HackableObject;
class Portal;
class Sound;

class DispelIllusionBehavior : public Component
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
	typedef Component super;

	void onDispelActivated();

	Portal* portal;
	HackableObject* object;
	std::string group;
	Sound* dispelSfx;

	static const std::string PropertyGroup;
	static const std::string SaveKeyDispelled;
};
