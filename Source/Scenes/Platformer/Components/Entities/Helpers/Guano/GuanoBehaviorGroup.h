#pragma once

#include "Engine/Components/GameComponentGroup.h"

class GuanoBehaviorGroup : public GameComponentGroup
{
public:
	static GuanoBehaviorGroup* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GuanoBehaviorGroup(GameObject* owner);
	virtual ~GuanoBehaviorGroup();

	void onLoad() override;

private:
	typedef GameComponentGroup super;
};
