#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyHealthBehavior : public GameComponent
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
	typedef GameComponent super;
	
	void saveState();

	Squally* squally;
};
