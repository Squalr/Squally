#pragma once

#include "Engine/Components/GameComponent.h"

class Grim;

class GrimManaBehavior : public GameComponent
{
public:
	static GrimManaBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	GrimManaBehavior(GameObject* owner);
	virtual ~GrimManaBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;
	
	void saveState();

	Grim* grim = nullptr;
};
