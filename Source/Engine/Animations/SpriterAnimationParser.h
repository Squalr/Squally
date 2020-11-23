#pragma once
#include <map>
#include <stack>

#include "cocos/base/CCValue.h"
#include "cocos/math/Vec2.h"
#include "cocos/platform/CCSAXParser.h"

struct SpriterBoneRef
{
	int id;
	int parent; // nullable => -1
	int timeline;
	int key;

	SpriterBoneRef(int id, int parent, int timeline, int key)
		: id(id), parent(parent), timeline(timeline), key(key) { }
};

struct SpriterBone
{
	cocos2d::Vec2 position;
	cocos2d::Vec2 scale;
	float angle;

	SpriterBone(cocos2d::Vec2 position, cocos2d::Vec2 scale, float angle)
		: position(position), scale(scale), angle(angle) { }
};

struct SpriterObjectRef
{
	int id;
	int parent;
	int timeline;
	int key;
	int zIndex;

	SpriterObjectRef(int id, int parent, int timeline, int key, int zIndex)
		: id(id), parent(parent), timeline(timeline), key(key), zIndex(zIndex) { }
};

struct SpriterObject
{
	int folderId;
	int fileId;
	cocos2d::Vec2 position;
	cocos2d::Vec2 scale;
	float angle;

	SpriterObject(int folderId, int fileId, cocos2d::Vec2 position, cocos2d::Vec2 scale, float angle)
		: folderId(folderId), fileId(fileId), position(position), scale(scale), angle(angle) { }
};

struct SpriterMainlineKey
{
	int id;
	float time;
	std::vector<SpriterObjectRef> objectRefs;
	std::vector<SpriterBoneRef> boneRefs;

	SpriterMainlineKey(int id, float time)
		: id(id), time(time), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
};

struct SpriterTimelineKey
{
	int id;
	int spin;
	float time;
	std::vector<SpriterObject> objects;
	std::vector<SpriterBone> bones;

	SpriterTimelineKey(int id, int spin, float time)
		: id(id), spin(spin), time(time), objects(std::vector<SpriterObject>()), bones(std::vector<SpriterBone>()) { }
};

struct SpriterTimeline
{
	int id;
	int object;
	std::string name;
	std::string objectType;
	std::vector<SpriterTimelineKey> keys;

	SpriterTimeline(int id, int object, std::string name, std::string objectType)
		: id(id), object(object), name(name), objectType(objectType), keys(std::vector<SpriterTimelineKey>()) { }
};

struct SpriterMainline
{
	std::vector<SpriterMainlineKey> keys;
	
	SpriterMainline() : keys(std::vector<SpriterMainlineKey>()) { }
};

struct SpriterAnimation
{
	int id;
	std::string name;
	float length;
	float interval;
	bool isLooping;
	SpriterMainline mainline;
	std::vector<SpriterTimeline> timelines;

	SpriterAnimation(int id, std::string name, float length, float interval, bool isLooping)
		: id(id), name(name), length(length), interval(interval), isLooping(isLooping), mainline(SpriterMainline()), timelines(std::vector<SpriterTimeline>()) { }
};

struct SpriterObjectInfo
{
	std::string name;
	std::string type;
	cocos2d::Vec2 size;

	SpriterObjectInfo(std::string name, std::string type, cocos2d::Vec2 size)
		: name(name), type(type), size(size) { }
};

struct SpriterEntity
{
	int id;
	std::string name;
	std::vector<SpriterObjectInfo> objectInfo;
	std::vector<SpriterAnimation> animations;

	SpriterEntity(int id, std::string name)
		: id(id), name(name), objectInfo(std::vector<SpriterObjectInfo>()), animations(std::vector<SpriterAnimation>()) { }
};

struct SpriterFile
{
	int id;
	std::string name;
	cocos2d::Vec2 size;
	cocos2d::Vec2 anchor;

	SpriterFile(int id, std::string name, cocos2d::Vec2 size, cocos2d::Vec2 anchor)
		: id(id), name(name), size(size), anchor(anchor) { }
};

struct SpriterFolder
{
	int id;
	std::vector<SpriterFile> files;

	SpriterFolder(int id) : id(id), files(std::vector<SpriterFile>()) { }
};

struct SpriterData
{
	std::vector<SpriterFolder> folders;
	std::vector<SpriterEntity> entities;
};

class SpriterAnimationParser : public cocos2d::SAXDelegator
{
public:
	static SpriterData Parse(std::string animationResource);

protected:
	SpriterAnimationParser();
	virtual ~SpriterAnimationParser();

	static bool ParseXMLFile(const std::string& xmlFilename);
    void startElement(void* ctx, const char* name, const char** atts) override;
    void endElement(void* ctx, const char* name) override;
    void textHandler(void* ctx, const char* ch, size_t len) override;

private:
	static SpriterData CurrentParse;

	static SpriterAnimationParser* Instance;
	
	enum class AttributeFocus
	{
		Data,
		Folder,
		File,
		Entity,
		ObjectInfo,
		Animation,
		Mainline,
		Timeline,
		Key,
		Object,
		ObjectRef,
		Bone,
		BoneRef,
	};

	static std::stack<AttributeFocus> FocusStack;
	static std::map<std::string, SpriterData> SpriterDataCache;

	static const std::string AttributeSpriterData;
	static const std::string AttributeFolder;
	static const std::string AttributeFile;
	static const std::string AttributeEntity;
	static const std::string AttributeObjectInfo;
	static const std::string AttributeAnimation;
	static const std::string AttributeMainline;
	static const std::string AttributeTimeline;
	static const std::string AttributeKey;
	static const std::string AttributeObject;
	static const std::string AttributeObjectRef;
	static const std::string AttributeBone;
	static const std::string AttributeBoneRef;
};
