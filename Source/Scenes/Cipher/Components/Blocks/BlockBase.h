#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

namespace cocos2d
{
	class Sprite;
}

class Bolt;
class ClickableNode;
class LocalizedLabel;
class LocalizedString;

class BlockBase : public CipherComponentBase
{
public:
	enum class BlockType
	{
		Toolbox,
		Normal,
		Static,
	};

	void removeConnections();

protected:
	enum class ConnectionType
	{
		None,
		Single,
		Double
	};

	BlockBase(BlockType blockType, ConnectionType inputType, ConnectionType outputType, ClickableNode* block, std::string iconResource, LocalizedString* label);
	~BlockBase();

	void initializePositions() override;
	void initializeListeners() override;
	virtual BlockBase* spawn() = 0;
	bool isInGameArea();

	BlockType blockType;

private:
	typedef CipherComponentBase super;

	ClickableNode* block;
	cocos2d::Sprite* icon;
	LocalizedLabel* label;
	std::vector<Bolt*> inputBolts;
	std::vector<Bolt*> outputBolts;
	
	ConnectionType inputType;
	ConnectionType outputType;
	cocos2d::Vec2 originalPosition;
	cocos2d::Vec2 clickDelta;
};
