#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyHealthBehavior : public Component
{
public:
	static SquallyHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyHealthBehavior(GameObject* owner);
	virtual ~SquallyHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;
	
	void saveState();

	Squally* squally;
};
