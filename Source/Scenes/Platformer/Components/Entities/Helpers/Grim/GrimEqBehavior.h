#pragma once

#include "Engine/Components/GameComponent.h"

class Grim;

class GrimEqBehavior : public GameComponent
{
public:
	static GrimEqBehavior* create(GameObject* owner);

	static const std::string MapKey;
	static const int DefaultLevel;

protected:
	GrimEqBehavior(GameObject* owner);
	virtual ~GrimEqBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Grim* grim = nullptr;
};
