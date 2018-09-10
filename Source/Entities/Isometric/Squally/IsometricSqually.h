#pragma once
#include <mutex>
#include "cocos2d.h"

#include "Engine/Input/InputManager.h"
#include "Entities/Isometric/IsometricEntity.h"
#include "Events/NavigationEvents.h"
#include "Resources.h"

using namespace cocos2d;

class IsometricSqually : public IsometricEntity
{
public:
	static IsometricSqually * deserialize(ValueMap* initProperties);
	static IsometricSqually * getInstance();

	static const std::string KeySquallyProperty;

protected:
	Vec2 getButtonOffset() override;

private:
	IsometricSqually(ValueMap* initProperties);
	~IsometricSqually();

	void registerHackables();
	void onEnter() override;
	void update(float) override;

	InputManager* inputManager;

	static IsometricSqually* squallyInstance;
};
