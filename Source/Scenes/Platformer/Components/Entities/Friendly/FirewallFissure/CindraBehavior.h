#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class CindraBehavior : public GameComponent
{
public:
	static CindraBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	CindraBehavior(GameObject* owner);
	virtual ~CindraBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void setPostText();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
