#pragma once
#include <set>

#include "Engine/Maps/SerializableObject.h"

namespace cocos2d
{
	class ParticleSystem;
}

class CollisionObject;
class InteractMenu;

class HackableHint : public SerializableObject
{
public:
	static HackableHint* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyHackableHint;

protected:
	HackableHint(cocos2d::ValueMap& initProperties);
	virtual ~HackableHint();
	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SerializableObject super;

	InteractMenu* interactMenu;
	CollisionObject* hintCollision;
};
