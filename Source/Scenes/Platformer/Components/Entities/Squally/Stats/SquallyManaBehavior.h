#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyManaBehavior : public GameComponent
{
public:
	static SquallyManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyManaBehavior(GameObject* owner);
	virtual ~SquallyManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void saveState();

	Squally* squally = nullptr;
};
