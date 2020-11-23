#pragma once
#include <vector>

#include "cocos/math/Vec2.h"

// TODO: Variables, events, sounds

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

enum class SpriterCurveType
{
	Instant,
	Linear,
	Quadratic,
	Cubic,
	Quartic,
	Quintic,
	Bezier,
};

struct SpriterMainlineKey
{
	int id;
	float time;
	SpriterCurveType curveType;
	float c1;
	float c2;
	float c3;
	float c4;
	std::vector<SpriterObjectRef> objectRefs;
	std::vector<SpriterBoneRef> boneRefs;

	SpriterMainlineKey(int id, float time, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
		: id(id), time(time), curveType(curveType), c1(c1), c2(c2), c3(c3), c4(c4), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
	SpriterMainlineKey() : id(-1), time(0.0f), curveType(SpriterCurveType::Linear), c1(0.0f), c2(0.0f), c3(0.0f), c4(0.0f), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
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
	SpriterAnimation() : id(-1), name(""), length(0.0f), interval(0.0f), isLooping(false), mainline(SpriterMainline()), timelines(std::vector<SpriterTimeline>()) { }
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
