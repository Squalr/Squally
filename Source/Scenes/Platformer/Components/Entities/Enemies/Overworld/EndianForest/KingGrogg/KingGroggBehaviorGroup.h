#pragma once

#include "Engine/Components/GameComponentGroup.h"

class KingGroggBehaviorGroup : public GameComponentGroup
{
public:
	static KingGroggBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	KingGroggBehaviorGroup(GameObject* owner);
	virtual ~KingGroggBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
