#pragma once

#include "Engine/Components/GameComponent.h"

class ChestBase;
class DialogueOption;
class PlatformerEntity;
class Scrappy;
class Squally;

class BurchBehavior : public GameComponent
{
public:
	static BurchBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	BurchBehavior(GameObject* owner);
	virtual ~BurchBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void refreshPreText();

	ChestBase* chest = nullptr;
	DialogueOption* dialogueOption = nullptr;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	static const std::string SaveKeyAskedPermission;
};
