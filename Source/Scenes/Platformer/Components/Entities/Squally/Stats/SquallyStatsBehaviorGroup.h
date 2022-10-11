#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SquallyStatsBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyStatsBehaviorGroup(GameObject* owner);
	virtual ~SquallyStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
