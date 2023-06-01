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
	static const std::string SaveKeyItemAGiven;
	static const std::string SaveKeyItemBGiven;
	static const std::string SaveKeyItemCGiven;
	static const std::string SaveKeyItemDGiven;
	static const std::string SaveKeyItemEGiven;
	static const std::string SaveKeyItemFGiven;
	static const std::string SaveKeyItemGGiven;

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
