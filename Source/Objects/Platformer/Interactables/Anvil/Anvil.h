#pragma once

#include "Objects/Platformer/Interactables/InteractObject.h"

namespace cocos2d
{
	class Sprite;
}

class Item;
class MinMaxPool;
class RecipePoolDeserializer;
class SmartAnimationSequenceNode;
class WorldSound;

class Anvil : public InteractObject
{
public:
	static Anvil* create(cocos2d::ValueMap& properties);
	
	void activate();
	void deactivate();

	static const std::string MapKey;

protected:
	Anvil(cocos2d::ValueMap& properties);
	virtual ~Anvil();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract() override;

private:
	typedef InteractObject super;

	void loadRecipePool();

	cocos2d::Sprite* anvil;
	cocos2d::Node* floatContainer;
	cocos2d::Sprite* shine;
	cocos2d::Sprite* hammer;
	std::string recipePoolName;
	MinMaxPool* recipePool;
	std::vector<Item*> recipes;
	RecipePoolDeserializer* recipePoolDeserializer;
};
