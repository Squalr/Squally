#pragma once

#include "Engine/Components/GameComponent.h"

class Portal;

class DisabledPortal : public GameComponent
{
public:
	static DisabledPortal* create(GameObject* owner);

	void enablePortal();

	static const std::string MapKey;

protected:
	DisabledPortal(GameObject* owner);
	virtual ~DisabledPortal();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	Portal* portal = nullptr;
};
