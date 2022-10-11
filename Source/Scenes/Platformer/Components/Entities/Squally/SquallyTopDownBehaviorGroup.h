#pragma once

#include "Engine/Components/GameComponentGroup.h"

class SquallyTopDownBehaviorGroup : public GameComponentGroup
{
public:
	static SquallyTopDownBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyTopDownBehaviorGroup(GameObject* owner);
	virtual ~SquallyTopDownBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
