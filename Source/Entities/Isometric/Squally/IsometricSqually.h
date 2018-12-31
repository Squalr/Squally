#pragma once

#include "Entities/Isometric/IsometricEntity.h"

class IsometricSqually : public IsometricEntity
{
public:
	static IsometricSqually* deserialize(cocos2d::ValueMap* initProperties);
	static IsometricSqually* getInstance();

	static const std::string KeySquallyProperty;

protected:
	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef IsometricEntity super;
	IsometricSqually(cocos2d::ValueMap* initProperties);
	~IsometricSqually();

	void registerHackables();
	void onEnter() override;
	void update(float) override;

	static IsometricSqually* squallyInstance;
};
