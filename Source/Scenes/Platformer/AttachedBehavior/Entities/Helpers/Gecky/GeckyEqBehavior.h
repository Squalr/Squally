#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Gecky;

class GeckyEqBehavior : public AttachedBehavior
{
public:
	static GeckyEqBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyEqBehavior(GameObject* owner);
	virtual ~GeckyEqBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	Gecky* guano;
};
