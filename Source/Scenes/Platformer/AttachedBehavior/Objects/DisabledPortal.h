#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class Portal;

class DisabledPortal : public AttachedBehavior
{
public:
	static DisabledPortal* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	DisabledPortal(GameObject* owner);
	~DisabledPortal();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Portal* portal;
};
