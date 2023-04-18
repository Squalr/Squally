#pragma once

#include "Engine/Components/GameComponent.h"

class Grim;

class GrimHealthBehavior : public GameComponent
{
public:
	static GrimHealthBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimHealthBehavior(GameObject* owner);
	virtual ~GrimHealthBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void saveState();

	Grim* grim = nullptr;
};
