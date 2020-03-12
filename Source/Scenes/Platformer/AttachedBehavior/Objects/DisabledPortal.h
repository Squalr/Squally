#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Portal;

class DisabledPortal : public AttachedBehavior
{
public:
	static DisabledPortal* create(GameObject* owner);

	void enablePortal();

	static const std::string MapKeyAttachedBehavior;

protected:
	DisabledPortal(GameObject* owner);
	virtual ~DisabledPortal();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	Portal* portal;
};
