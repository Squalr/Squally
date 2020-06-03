#pragma once

#include "Engine/Maps/GameObject.h"

namespace cocos2d
{
	class Sprite;
}

class Sarcophagus : public GameObject
{
public:
	static Sarcophagus* create(cocos2d::ValueMap& properties);

	cocos2d::Sprite* getBase();
	cocos2d::Sprite* getLid();

	static const std::string MapKey;

protected:
	Sarcophagus(cocos2d::ValueMap& properties);
	virtual ~Sarcophagus();

	void initializePositions();
	void initializeListeners();

private:
	typedef GameObject super;

	cocos2d::Sprite* sarcophagusBase;
	cocos2d::Sprite* sarcophagusLid;
};
