#pragma once
#include "cocos2d.h"

#include "Entities/Isometric/IsometricEntity.h"
#include "Events/NavigationEvents.h"

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

	static IsometricSqually* squallyInstance;
};
