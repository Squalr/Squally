#pragma once

#include "Engine/Components/GameComponentGroup.h"

class FriendlyCombatBehaviorGroup : public GameComponentGroup
{
public:
	static FriendlyCombatBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyCombatBehaviorGroup(GameObject* owner);
	virtual ~FriendlyCombatBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
