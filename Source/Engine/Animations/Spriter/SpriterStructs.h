#pragma once
#include <vector>

#include "cocos/math/Vec2.h"
#include "cocos/math/CCGeometry.h"

// TODO: Variables, events, sounds

struct SpriterBoneRef
{
	int id = -1;
	int parent = -1; // nullable => -1
	int timeline = -1;
	int key = -1;

	SpriterBoneRef(int id, int parent, int timeline, int key)
		: id(id), parent(parent), timeline(timeline), key(key) { }
};

struct SpriterBone
{
	cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 scale = cocos2d::Vec2::ZERO;
	float angle = 0.0f;
	float alpha = 0.0f;

	SpriterBone() : position(cocos2d::Vec2::ZERO), scale(cocos2d::Vec2::ZERO), angle(0.0f), alpha(1.0f) { }
	SpriterBone(cocos2d::Vec2 position, cocos2d::Vec2 scale, float angle, float alpha)
		: position(position), scale(scale), angle(angle), alpha(alpha) { }
};

struct SpriterObjectRef
{
	int id = -1;
	int parent = -1;
	int timeline = -1;
	int key = -1;
	int zIndex = 0;

	SpriterObjectRef() { }
	SpriterObjectRef(int id, int parent, int timeline, int key, int zIndex)
		: id(id), parent(parent), timeline(timeline), key(key), zIndex(zIndex) { }
};

struct SpriterObject
{
	int folderId = -1;
	int fileId = -1;
	cocos2d::Vec2 position = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 anchor = cocos2d::Vec2::ZERO;
	cocos2d::Vec2 scale = cocos2d::Vec2::ZERO;
	float angle = 0.0f;
	float alpha = 1.0f;

	SpriterObject() { }
	SpriterObject(int folderId, int fileId, cocos2d::Vec2 position, cocos2d::Vec2 anchor, cocos2d::Vec2 scale, float angle, float alpha)
		: folderId(folderId), fileId(fileId), position(position), anchor(anchor), scale(scale), angle(angle), alpha(alpha) { }
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
	int id = -1;
	int time = 0;
	SpriterCurveType curveType = SpriterCurveType::Linear;
	float c1 = 0.0f;
	float c2 = 0.0f;
	float c3 = 0.0f;
	float c4 = 0.0f;
	std::vector<SpriterObjectRef> objectRefs;
	std::vector<SpriterBoneRef> boneRefs;

	SpriterMainlineKey(int id, int time, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
		: id(id), time(time), curveType(curveType), c1(c1), c2(c2), c3(c3), c4(c4), objectRefs(std::vector<SpriterObjectRef>()), boneRefs(std::vector<SpriterBoneRef>()) { }
	SpriterMainlineKey() { }
};

enum class SpriterObjectType
{
	Object,
	Bone,
};

struct SpriterTimelineKey
{
	int id = -1;
	int spin = -1;
	int time = -1;
	SpriterCurveType curveType = SpriterCurveType::Linear;
	float c1 = 0.0f;
	float c2 = 0.0f;
	float c3 = 0.0f;
	float c4 = 0.0f;
	SpriterObject object;
	SpriterBone bone;
	SpriterObjectType objectType = SpriterObjectType::Object;

	SpriterTimelineKey(int id, int spin, int time, SpriterCurveType curveType, float c1, float c2, float c3, float c4)
		: id(id), spin(spin), time(time), curveType(curveType), c1(c1), c2(c2), c3(c3), c4(c4), object(SpriterObject()), bone(SpriterBone()) { }
};

struct SpriterTimeline
{
	int id = -1;
	int object = -1;
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
	int id = -1;
	std::string name;
	float length = 0.0f;
	float interval = 0.0f;
	bool isLooping = false;
	SpriterMainline mainline;
	std::vector<SpriterTimeline> timelines;

	SpriterAnimation(int id, std::string name, float length, float interval, bool isLooping)
		: id(id), name(name), length(length), interval(interval), isLooping(isLooping), mainline(SpriterMainline()), timelines(std::vector<SpriterTimeline>()) { }
	SpriterAnimation() { }
};

struct SpriterObjectInfo
{
	std::string name;
	std::string type;
	cocos2d::CSize size;

	SpriterObjectInfo(std::string name, std::string type, cocos2d::CSize size)
		: name(name), type(type), size(size) { }
};

struct SpriterEntity
{
	int id = -1;
	std::string name;
	std::vector<SpriterObjectInfo> objectInfo;
	std::vector<SpriterAnimation> animations;

	SpriterEntity(int id, std::string name)
		: id(id), name(name), objectInfo(std::vector<SpriterObjectInfo>()), animations(std::vector<SpriterAnimation>()) { }
};

struct SpriterFile
{
	unsigned int id = -1;
	std::string name;
	cocos2d::CSize size;
	cocos2d::Vec2 anchor = cocos2d::Vec2::ZERO;

	SpriterFile(unsigned int id, std::string name, cocos2d::CSize size, cocos2d::Vec2 anchor)
		: id(id), name(name), size(size), anchor(anchor) { }
};

struct SpriterFolder
{
	unsigned int id = -1;
	std::vector<SpriterFile> files;

	SpriterFolder(unsigned int id) : id(id) { }
};

struct SpriterData
{
	std::vector<SpriterFolder> folders;
	std::vector<SpriterEntity> entities;

	// Precomputed {animationId => {timeline id => {bone name => bone ID map}}}
	std::map<int, std::map<std::string, int>> boneMap;
};
