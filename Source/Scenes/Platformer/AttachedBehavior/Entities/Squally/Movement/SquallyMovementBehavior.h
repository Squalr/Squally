#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Squally;

class SquallyMovementBehavior : public AttachedBehavior
{
public:
	static SquallyMovementBehavior* create(GameObject* owner);

	void disablePositionSaving();

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyMovementBehavior(GameObject* owner);
	~SquallyMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	void onMovementChanged();

	Squally* squally;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

	bool isDisposing;
	bool isPositionSavingDisabled;
};
