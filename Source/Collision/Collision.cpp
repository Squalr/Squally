#include "Collision.h"

PhysicsShape* Collision::GetCollidingObject(PhysicsBody* self, PhysicsContact& contact)
{
	if (contact.getShapeA()->getBody() != self && contact.getShapeB()->getBody() != self)
	{
		return false;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody() == self)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	return other;
}

bool Collision::IsContactBelow(Node* node, PhysicsContact& contact)
{
	for (int index = 0; index < contact.getContactData()->count; index++)
	{
		if (contact.getContactData()->points[index].y < node->getPositionY())
		{
			return true;
		}
	}

	return false;
}
