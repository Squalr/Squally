#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Gecky;

class GeckyHealthBehavior : public AttachedBehavior
{
public:
	static GeckyHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyHealthBehavior(GameObject* owner);
	virtual ~GeckyHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();

	Gecky* guano;
};
