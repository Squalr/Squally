#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyManaBehavior : public Component
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
	typedef Component super;
	
	void saveState();

	Squally* squally;
};
