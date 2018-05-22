#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Objects/Objects.h"

using namespace cocos2d;

class LevelMap : public Node
{
public:
	static LevelMap* create(std::string initLevelMapFileName, Size initMapSize);

	void insertStaticMember(Node* node, bool hackerModeHidden);
	void insertDynamicMember(Node* node, bool hackerModeHidden);

	void setPosition(const Vec2& position) override;
	Size getMapSize();
	void hackerModeEnable();
	void hackerModeDisable();
	std::string getMapFileName();

protected:
	LevelMap(std::string initLevelMapFileName, Size initMapSize);
	~LevelMap();

private:

	std::string levelMapFileName;
	Size mapSize;

	std::vector<Node*>* staticMembers;
	std::vector<Node*>* dynamicMembers;
	std::vector<Node*>* hackerModeHiddenMembers;
};
