#include "cocos2d.h"

class Game : public cocos2d::Scene
{
public:
	virtual bool init();

	static cocos2d::Scene* createScene();

	// A selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// Implement the "static create()" method manually
	CREATE_FUNC(Game);
};
