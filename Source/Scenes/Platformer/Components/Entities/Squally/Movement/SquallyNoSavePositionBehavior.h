#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyNoSavePositionBehavior : public Component
{
public:
	static SquallyNoSavePositionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyNoSavePositionBehavior(GameObject* owner);
	virtual ~SquallyNoSavePositionBehavior();

	void onEnter() override;
	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	Squally* squally;
};
