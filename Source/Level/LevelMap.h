#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Objects.h"

using namespace cocos2d;

class LevelMap : public Node
{
public:
	static LevelMap* create();

	void insertStaticMember(Node* node, bool hackerModeHidden);
	void insertDynamicMember(Node* node, bool hackerModeHidden);

	static Size mapSize;

	void setPosition(const Vec2& position) override;
	void hackerModeEnable();
	void hackerModeDisable();

protected:
	LevelMap();
	~LevelMap();

private:
	std::vector<Node*>* staticMembers;
	std::vector<Node*>* dynamicMembers;
	std::vector<Node*>* hackerModeHiddenMembers;
};
