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

class AncientAnvil : public InteractObject
{
public:
	static AncientAnvil* create(cocos2d::ValueMap& properties);
	
	void activate();
	void deactivate();

	static const std::string MapKey;

protected:
	AncientAnvil(cocos2d::ValueMap& properties);
	virtual ~AncientAnvil();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onInteract(PlatformerEntity* interactingEntity) override;

private:
	typedef InteractObject super;

	void loadRecipePool();

	cocos2d::Sprite* anvil = nullptr;
	cocos2d::Node* floatContainer = nullptr;
	cocos2d::Sprite* shine = nullptr;
	cocos2d::Sprite* hammer = nullptr;
	std::string recipePoolName;
	MinMaxPool* recipePool = nullptr;
	std::vector<Item*> recipes;
	RecipePoolDeserializer* recipePoolDeserializer = nullptr;
};
