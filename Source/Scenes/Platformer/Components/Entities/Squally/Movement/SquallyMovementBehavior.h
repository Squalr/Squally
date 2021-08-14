#pragma once

#include "Engine/Components/GameComponent.h"

class Squally;

class SquallyMovementBehavior : public GameComponent
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
	typedef GameComponent super;

	void onMovementChanged();
	void saveSquallyPosition();
	void loadSquallyPosition();

	Squally* squally = nullptr;

	bool isDisposing = false;
	bool isPositionSavingDisabled = false;

	static int LeftPressedKeys;
	static int RightPressedKeys;
	static int UpPressedKeys;
	static int DownPressedKeys;
};
