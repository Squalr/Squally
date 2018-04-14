#ifndef SPRITERDOCUMENTLOADER_H
#define SPRITERDOCUMENTLOADER_H

#include "../../spriterengine/global/global.h"

#include "../../spriterengine/override/spriterfiledocumentwrapper.h"

#include "../../spriterengine/loading/loadinghelpers.h"

namespace SpriterEngine
{
	class SpriterFileDocumentWrapper;
	class SpriterFileElementWrapper;
	class SpriterFileAttributeWrapper;

	class SpriterModel;
	class Entity;
	class VariableContainer;
	class Animation;
	class Object;
	class TimeInfo;
	class EasingCurveInterface;
	class UniversalObjectInterface;
	class Timeline;
	class MainlineKey;
	class FileFlattener;

	class SpriterDocumentLoader
	{
	public:
		void loadFile(SpriterModel *model, SpriterFileDocumentWrapper *documentWrapper, const std::string &fileName);

	private:
		void getAtlasFromElement(SpriterFileElementWrapper * spriterDataElement, SpriterModel * model, std::string scmlFileName);
		void getFolderFileStructureFromElement(SpriterFileElementWrapper * spriterDataElement, SpriterModel * model, std::string scmlFileName, FileFlattener * fileFlattener);
		void getTagListFromElement(SpriterFileElementWrapper * spriterDataElement, SpriterModel * model);

		void getEntitiesFromElement(SpriterFileElementWrapper * spriterDataElement, SpriterModel * model, FileFlattener * fileFlattener);
		Entity * getNewEntityFromEntityElement(SpriterFileElementWrapper * entityElement, SpriterModel * model);
		void getObjectInfoFromEntityElement(SpriterFileElementWrapper * entityElement, Entity * entity, PointMap *defaultBoxPivotMap);

		void getVarDefArrayFromElement(SpriterFileElementWrapper * parentObjectElement, VariableContainer * parentObjectAsVariableContainer);

		void getCharacterMapsFromEntityElement(SpriterFileElementWrapper * entityElement, SpriterModel * model, Entity * entity, FileFlattener * fileFlattener);

		void getAnimationsFromEntityElement(SpriterFileElementWrapper * entityElement, SpriterModel * model, Entity * entity, FileFlattener * fileFlattener, PointMap *defaultBoxPivotMap);
		Animation * getNewAnimationFromAnimationElement(SpriterFileElementWrapper * animationElement, Entity * entity);

		void getTimelinesFromAnimationElement(SpriterFileElementWrapper * animationElement, SpriterModel * model, Entity * entity, Animation * animation, FileFlattener * fileFlattener, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap * subEntityKeyInfoMap, PointMap *defaultBoxPivotMap, BooleanVector *timelineRedunantKeyedVector);

		bool createRedundantFirstKeys(Animation * animation, Timeline * timeline);

		void getMetaDataFromElement(SpriterFileElementWrapper *parentObjectElement, SpriterModel *model, Entity *entity, Animation *animation, int objectId);

		void getVarlinesFromMetaDataElement(SpriterFileElementWrapper *animationElement, Entity *entity, Animation *animation, int objectId);

		UniversalObjectInterface * getObjectInfoFromVariableKeyElement(SpriterFileElementWrapper *variableKeyElement, Variable *variable);

		void getTaglinesFromMetaDataElement(SpriterFileElementWrapper *metaDataElement, SpriterModel *model, Animation *animation, int objectId);

		UniversalObjectInterface * getObjectInfoFromTagKeyElement(SpriterFileElementWrapper *tagKeyElement, SpriterModel *model);

		Object * getObjectFromTimelineElement(SpriterFileElementWrapper * timelineElement, Entity * entity);

		TimeInfo * getTimeInfoFromElement(SpriterFileElementWrapper * validCurrentKeyElement, SpriterFileElementWrapper * nextKeyElement, SpriterFileElementWrapper * validFirstKeyElement, real animationLength, bool animationLooping);
		EasingCurveInterface * getEasingCurveFromKeyElement(SpriterFileElementWrapper *element);

		UniversalObjectInterface * getObjectInfoFromTimelineKeyElement(SpriterFileElementWrapper * keyElement, Entity * entity, Object * object, Timeline * timeline, FileFlattener * fileFlattener, SpriteKeyFileInfo * spriteKeyFileInfo, SubEntityKeyInfo *subEntityKeyInfo, point *defaultBoxPivot);

		void getMainlineFromAnimationElement(SpriterFileElementWrapper * animationElement, Animation * animation, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap, BooleanVector *timelineRedunantKeyedVector);
		void getRefsFromMainlineKeyElement(SpriterFileElementWrapper * keyElement, Animation * animation, MainlineKey * mainlineKey, SpriteKeyFileInfoObjectIdMap * spriteKeyFileInfoMap, SubEntityKeyInfoMap *subEntityKeyInfoMap, BooleanVector *timelineRedunantKeyedVector);

		void getEventlinesFromAnimationElement(SpriterFileElementWrapper * animationElement, Entity * entity, Animation * animation);

		void getSoundlinesFromAnimationElement(SpriterFileElementWrapper * animationElement, Entity * entity, Animation * animation, FileFlattener * fileFlattener);
		UniversalObjectInterface * getSoundObjectInfoFromSoundlineKey(SpriterFileElementWrapper * keyElement, Entity * entity, Object *object, FileFlattener * fileFlattener, bool * soundFileFound);
	};

}

#endif // SPRITERDOCUMENTLOADER_H
