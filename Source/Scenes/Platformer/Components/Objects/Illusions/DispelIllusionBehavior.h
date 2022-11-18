#pragma once

#include "Engine/Components/GameComponent.h"

class HackableObject;
class Portal;
class Sound;

class DispelIllusionBehavior : public GameComponent
{
public:
	static DispelIllusionBehavior* create(GameObject* owner);
	
	void onDispelActivated();

	static const std::string MapKey;

protected:
	DispelIllusionBehavior(GameObject* owner);
	virtual ~DispelIllusionBehavior();

	void onLoad() override;
	void onDisable() override;
	void registerHackables();

private:
	typedef GameComponent super;

	Portal* portal = nullptr;
	HackableObject* object = nullptr;
	std::string group;
	Sound* dispelSfx = nullptr;

	static const std::string PropertyGroup;
	static const std::string SaveKeyDispelled;
};
