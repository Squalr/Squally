#pragma once

#include "Engine/Components/Component.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class CypressBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
