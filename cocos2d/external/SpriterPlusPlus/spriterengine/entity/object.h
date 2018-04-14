#ifndef OBJECT_H
#define OBJECT_H

#include <vector>

#include "../variable/variablecontainer.h"

#include "../global/global.h"


namespace SpriterEngine
{

	class UniversalObjectInterface;
	class VariableInstanceNameAndIdMap;
	class ObjectFactory;
	class SpriterModel;
	class EntityInstance;
	class EntityInstanceData;

	typedef std::vector<Variable*> VariableVector;
	typedef std::vector<int> IdVector;

	class Object : public VariableContainer
	{
	public:
		enum ObjectType 
		{
			OBJECTTYPE_NONE,
			OBJECTTYPE_POINT,
			OBJECTTYPE_BONE,
			OBJECTTYPE_BOX,
			OBJECTTYPE_SPRITE,
			OBJECTTYPE_ENTITY,
			OBJECTTYPE_SOUND,
			OBJECTTYPE_TRIGGER
		};

		Object(std::string initialName, int initialId, ObjectType initialObjectType);

		std::string getName();
		int getId();
		ObjectType getType();

		void addInitializationId(int newId);
		void setSize(point newSize);

		UniversalObjectInterface *getNewObjectInfoInstance();

		virtual void addObjectInstanceToEntityInstanceData(SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);

	private:
		std::string name;
		ObjectType objectType;
		int objectId;

		point size;
		IdVector initializationIds;
	};

}

#endif // OBJECT_H
