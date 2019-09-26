#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class HexusOpponentData;
class PlatformerEntity;

class HexusBehaviorBase : public AttachedBehavior
{
public:
	virtual HexusOpponentData* createOpponentData() = 0;

protected:
	HexusBehaviorBase(GameObject* owner);
	~HexusBehaviorBase();

	void onLoad() override;

	PlatformerEntity* entity;

private:
	typedef AttachedBehavior super;
};
