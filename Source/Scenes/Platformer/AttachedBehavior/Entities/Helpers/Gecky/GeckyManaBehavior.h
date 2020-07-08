#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Gecky;

class GeckyManaBehavior : public AttachedBehavior
{
public:
	static GeckyManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GeckyManaBehavior(GameObject* owner);
	virtual ~GeckyManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;
	
	void saveState();

	Gecky* guano;
};
