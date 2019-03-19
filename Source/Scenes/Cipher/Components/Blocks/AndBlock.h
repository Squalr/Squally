#pragma once

#include "Scenes/Cipher/Components/Blocks/BlockBase.h"

class AndBlock : public BlockBase
{
public:
	static AndBlock* create(bool isToolBoxItem = false);
	
protected:
	BlockBase* spawn() override;

private:
	typedef BlockBase super;
	AndBlock(bool isToolBoxItem);
	~AndBlock();

	void onEnter() override;
	void initializePositions() override;
};
