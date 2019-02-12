#pragma once

#include "Engine/Events/ObjectEvents.h"
#include "Engine/SmartNode.h"

namespace cocos2d
{
	class Node;
}

// This is a pseudo-physics object used to detect proximity to other objects
class ProximityObject : public SmartNode
{
public:
	static ProximityObject* create(float radius);

	bool isInProximityTo(cocos2d::Node* other);

	template<class T>
	std::vector<T*> getProximityObjects()
	{
		std::vector<T*> result = std::vector<T*>();

		ObjectEvents::QueryObjects<T>([&](T* object)
		{
			if (this->isInProximityTo(dynamic_cast<cocos2d::Node*>(object)))
			{
				result.push_back(object);
			}
		});

		return result;
	};

protected:
	ProximityObject(float radius);
	virtual	~ProximityObject();

	void onEnter() override;
	void initializePositions() override;
	void update(float) override;

private:
	typedef SmartNode super;

	float radius;
};
