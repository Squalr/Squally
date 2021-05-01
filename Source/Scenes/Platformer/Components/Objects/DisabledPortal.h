#pragma once

#include "Engine/Components/Component.h"

class Portal;

class DisabledPortal : public Component
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
	typedef Component super;

	Portal* portal;
};
