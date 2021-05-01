#pragma once

#include "Engine/Components/Component.h"

class Squally;

class SquallyMovementBehavior : public Component
{
public:
	static SquallyMovementBehavior* create(GameObject* owner);

	void disablePositionSaving();

	static const std::string MapKey;
	static const float SquallyMovementAcceleration;

protected:
	SquallyMovementBehavior(GameObject* owner);
	virtual ~SquallyMovementBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef Component super;

	void onMovementChanged();
	void saveSquallyPosition();
	void loadSquallyPosition();

	Squally* squally;

	bool leftPressed;
	bool rightPressed;
	bool upPressed;
	bool downPressed;

	bool isDisposing;
	bool isPositionSavingDisabled;
};
