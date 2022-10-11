#pragma once

#include "Engine/Components/GameComponent.h"

class GameComponentGroup : public GameComponent
{
public:

protected:
	GameComponentGroup(GameObject* owner, std::vector<GameComponent*> component);
	virtual ~GameComponentGroup();

private:
	typedef GameComponent super;
};

