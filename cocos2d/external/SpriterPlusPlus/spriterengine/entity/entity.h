#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <map>

#include "../animation/animation.h"
#include "../variable/variablecontainer.h"
#include "../charactermap/charactermapinterface.h"
#include "../charactermap/charactermap.h"

#include "object.h"

namespace SpriterEngine
{

	class AnimationInstance;
	class UniversalObjectInterface;
	class EntityInstance;
	class EntityInstanceData;
	class SpriterModel;
	class ObjectFactory;

	typedef std::vector<Animation*> AnimationVector;
	typedef std::map<std::string, Object> ObjectNameMap;
	typedef std::map<int, Object*> ObjectIdMap;
	typedef std::map<std::string, CharacterMap> CharacterMapMap;

	class Entity : public VariableContainer, private CharacterMapInterface
	{
	public:
		Entity(std::string initialName, int initialId, FileVector *initialFileVector);
		~Entity();

		int getId();

		std::string getName();

		EntityInstance *getNewEntityInstance(SpriterModel *model, ObjectFactory *objectFactory);
		void setupInstance(SpriterModel *model, EntityInstance *entityInstance, EntityInstanceData *entityInstanceData, ObjectFactory *objectFactory);

		Animation *pushBackAnimation(std::string animationName, real length, bool looping);
		
		Object *setObject(std::string objectName, Object::ObjectType objectType);
		Object *getObject(int objectId);

		Variable *getVariable(int objectId, int variableId);

		CharacterMap *addCharacterMap(std::string name);

		void applyCharacterMap(std::string mapName, FileReferenceVector *mappedFiles) override;
		void removeAllCharacterMaps(FileReferenceVector *mappedFiles) override;

		UniversalObjectInterface *getNewObjectInfoInstance(int objectId);

		void setupDefaultVariableTimelines();

	private:
		int entityId;

		std::string name;

		Object *setSpatialObject(std::string objectName, Object::ObjectType objectType);
		Object *setTriggerObject(std::string objectName);
		Object *setSubEntityObject(std::string objectName);
		Object *setSoundObject(std::string objectName);

		void setupAnimationInstances(EntityInstance *entityInstance, EntityInstanceData *entityInstanceData);
		void setupObjectInstance(Object * object, SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);
		void setupObjectInstances(SpriterModel * model, EntityInstance * entityInstance, EntityInstanceData * entityInstanceData, ObjectFactory * objectFactory);

		AnimationVector animations;
		ObjectNameMap objectNameMap;
		ObjectIdMap objectIdMap;
		CharacterMapMap characterMaps;

		ObjectIdMap triggerIdMap;
		ObjectIdMap soundIdMap;
		ObjectIdMap subEntityIdMap;

		FileVector *files;
	};

}

#endif // ENTITY_H
