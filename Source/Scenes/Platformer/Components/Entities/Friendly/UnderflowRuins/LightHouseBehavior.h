#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class DialogueOption;
class MayanDoor;
class PlatformerEntity;
class Scrappy;
class Squally;

class LightHouseBehavior : public GameComponent
{
public:
	static LightHouseBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	LightHouseBehavior(GameObject* owner);
	virtual ~LightHouseBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void onPuzzleSolved();
};
