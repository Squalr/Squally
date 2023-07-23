#pragma once

#include "Engine/Components/GameComponentGroup.h"

class GrimBehaviorGroup : public GameComponentGroup
{
public:
	static GrimBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimBehaviorGroup(GameObject* owner);
	virtual ~GrimBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
