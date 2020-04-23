#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;
class Scrappy;
class Squally;

class CypressBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	Scrappy* scrappy;
	Squally* squally;
};
