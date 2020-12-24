#pragma once
#include <vector>

#include "cocos/math/Vec2.h"
#include "cocos/math/CCGeometry.h"

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
	float alpha;

	SpriterBone() : position(cocos2d::Vec2::ZERO), scale(cocos2d::Vec2::ZERO), angle(0.0f), alpha(1.0f) { }
	SpriterBone(cocos2d::Vec2 position, cocos2d::Vec2 scale, float angle, float alpha)
		: position(position), scale(scale), angle(angle), alpha(alpha) { }
};

struct SpriterObjectRef
{
	int id;
	int parent;
	int timeline;
	int key;
	int zIndex;

	SpriterObjectRef() : id(-1), parent(-1), timeline(-1), key(-1), zIndex(0) { }
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
	float alpha;

	SpriterObject() : folderId(-1), fileId(-1), position(cocos2d::Vec2::ZERO), scale(cocos2d::Vec2::ZERO), angle(0.0f), alpha(1.0f) { }
	SpriterObject(int folderId, int fileId, cocos2d::Vec2 position, cocos2d::Vec2 scale, float angle, float alpha)
		: folderId(folderId), fileId(fileId), position(position), scale(scale), angle(angle), alpha(alpha) { }
};

enum class SpriterCurveType
{
	Inherit,
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
	int time;
	SpriterCurveType curveType;
	float c1;
	float c2;
	float c3;
	float c4;
	std::vector<SpriterObjectRef> objectRefs;
	std::vector<SpriterBoneRef> boneRefs;

	SpriterMainlineKey(int id, int time, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
		: id(id), time(time), curveType(curveType), c1(c1), c2(c2), c3(c3), c4(c4), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
	SpriterMainlineKey() : id(-1), time(0), curveType(SpriterCurveType::Linear), c1(0.0f), c2(0.0f), c3(0.0f), c4(0.0f), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
};

enum class SpriterObjectType
{
	Object,
	Bone,
};

struct SpriterTimelineKey
{
	int id;
	int spin;
	int time;
	SpriterCurveType curveType;
	float c1;
	float c2;
	float c3;
	float c4;
	SpriterObject object;
	SpriterBone bone;
	SpriterObjectType objectType;

	SpriterTimelineKey(int id, int spin, int time, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
		: id(id), spin(spin), time(time), curveType(curveType), c1(c1), c2(c2), c3(c3), c4(c4), object(SpriterObject()), bone(SpriterBone()) { }
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
	cocos2d::Size size;

	SpriterObjectInfo(std::string name, std::string type, cocos2d::Size size)
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
	unsigned int id;
	std::string name;
	cocos2d::Size size;
	cocos2d::Vec2 anchor;

	SpriterFile(unsigned int id, std::string name, cocos2d::Size size, cocos2d::Vec2 anchor)
		: id(id), name(name), size(size), anchor(anchor) { }
};

struct SpriterFolder
{
	unsigned int id;
	std::vector<SpriterFile> files;

	SpriterFolder(unsigned int id) : id(id), files(std::vector<SpriterFile>()) { }
};

struct SpriterData
{
	std::vector<SpriterFolder> folders;
	std::vector<SpriterEntity> entities;

	// Precomputed {animationId => {timeline id => {bone name => bone ID map}}}
	std::map<int, std::map<std::string, int>> boneMap;
};
