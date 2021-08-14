#pragma once

#include "Engine/Components/GameComponent.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class CypressBehavior : public GameComponent
{
public:
	static CypressBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const std::string SaveKeyItemGiven;

protected:
	CypressBehavior(GameObject* owner);
	virtual ~CypressBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;
	Scrappy* scrappy = nullptr;
	Squally* squally = nullptr;
};
