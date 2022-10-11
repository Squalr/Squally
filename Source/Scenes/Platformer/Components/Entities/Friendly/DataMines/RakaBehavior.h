#pragma once

#include "Engine/Components/GameComponent.h"

class DialogueOption;
class MayanDoor;
class PlatformerEntity;
class Scrappy;
class Squally;

class RakaBehavior : public GameComponent
{
public:
	static RakaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	RakaBehavior(GameObject* owner);
	virtual ~RakaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void removeDialogueOption();

	DialogueOption* dialogueOption = nullptr;
	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
	MayanDoor* mayanDoor = nullptr;
};
