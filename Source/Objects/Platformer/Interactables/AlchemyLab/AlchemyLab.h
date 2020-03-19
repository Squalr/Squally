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

class AlchemyLab : public InteractObject
{
public:
	static AlchemyLab* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	AlchemyLab(cocos2d::ValueMap& properties);
	virtual ~AlchemyLab();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract() override;

private:
	typedef InteractObject super;

	void loadRecipePool();

	cocos2d::Sprite* alchemyLab;
	cocos2d::Node* floatContainer;
	cocos2d::Sprite* shine;
	cocos2d::Sprite* potion;
	std::string recipePoolName;
	MinMaxPool* recipePool;
	std::vector<Item*> recipes;
	RecipePoolDeserializer* recipePoolDeserializer;
};
