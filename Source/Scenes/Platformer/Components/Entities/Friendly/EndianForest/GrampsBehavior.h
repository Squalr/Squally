#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class GrampsBehavior : public GameComponent
{
public:
	static GrampsBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrampsBehavior(GameObject* owner);
	virtual ~GrampsBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void setPostText();

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
