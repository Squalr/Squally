#pragma once

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Node;
}

class HackablePreview;

// This is a pseudo-physics object used to detect proximity to other objects
class ProximityObject : public HackableObject
{
public:
	static ProximityObject* create(float radius);

	void launchTowardsTarget(Node* target, cocos2d::Vec2 offset = cocos2d::Vec2::ZERO, float spinSpeed = 0.0f, cocos2d::Vec3 secondsPer256pxLinearDistance = cocos2d::Vec3(0.75f, 0.75f, 0.75f), cocos2d::Vec3 gravity = cocos2d::Vec3(0.0f, -768.0f, 0.0f));
	void setVelocity(cocos2d::Vec3 velocity);
	void setAcceleration(cocos2d::Vec3 acceleration);
	cocos2d::Vec3 getVelocity();
	cocos2d::Vec3 getAcceleration();
	bool isInProximityTo(cocos2d::Node* other);

	template<class T>
	std::vector<T*> getProximityObjects()
	{
		std::vector<T*> result = std::vector<T*>();

		ObjectEvents::QueryObjects(QueryObjectsArgs<T>([&](T* object)
		{
			if (this->isInProximityTo(dynamic_cast<cocos2d::Node*>(object)))
			{
				result.push_back(object);
			}
		}));

		return result;
	};

protected:
	ProximityObject(float radius);
	virtual	~ProximityObject();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;
	void registerHackables() override;
	HackablePreview* createDefaultPreview() override;
	virtual HackablePreview* createVelocityPreview();
	virtual HackablePreview* createAccelerationPreview();

	cocos2d::Node* contentNode;

private:
	typedef HackableObject super;

	float radius;
	cocos2d::Vec3 velocity;
	cocos2d::Vec3 acceleration;
};
