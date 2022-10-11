#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyNoSavePositionBehavior : public GameComponent
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
	typedef GameComponent super;

	Squally* squally = nullptr;
};
