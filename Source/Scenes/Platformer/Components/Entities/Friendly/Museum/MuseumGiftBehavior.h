#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class MuseumGiftBehavior : public GameComponent
{
public:
	static MuseumGiftBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	MuseumGiftBehavior(GameObject* owner);
	virtual ~MuseumGiftBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void setPostText();
	void setPostTextEF();
	void setPostTextUR();
	void setPostTextDM();
	void setPostTextCV();
	void setPostTextFF();
	void setPostTextLC();
	void setPostTextBP();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;

	std::string museumZone;

	static const std::string PropertyMuseumZone;
};
