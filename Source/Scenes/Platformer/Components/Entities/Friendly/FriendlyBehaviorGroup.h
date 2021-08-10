#pragma once

#include "Engine/Components/GameComponentGroup.h"

class FriendlyBehaviorGroup : public GameComponentGroup
{
public:
	static FriendlyBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	FriendlyBehaviorGroup(GameObject* owner);
	virtual ~FriendlyBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
