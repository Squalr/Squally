#pragma once

#include "Scenes/Cipher/Components/CipherComponentBase.h"

class AddBlock;
class AndBlock;
class BlockBase;
class BruteForceBlock;
class CshlBlock;
class CshrBlock;
class DivBlock;
class ImmediateBlock;
class InvBlock;
class LocalizedLabel;
class ModBlock;
class MulBlock;
class OrBlock;
class ScrollPane;
class ShlBlock;
class ShrBlock;
class SplitterBlock;
class SubBlock;
class XorBlock;

class ToolBox : public CipherComponentBase
{
public:
	static ToolBox* create();

protected:
	void onBeforeStateChange(CipherState* cipherState) override;
	void onAnyStateChange(CipherState* cipherState) override;

private:
	typedef CipherComponentBase super;
	ToolBox();
	~ToolBox();

	void onEnter() override;
	void initializePositions() override;

	ScrollPane* scrollPane;
	AddBlock* addBlock;
	AndBlock* andBlock;
	BruteForceBlock* bruteForceBlock;
	CshlBlock* cshlBlock;
	CshrBlock* cshrBlock;
	DivBlock* divBlock;
	ImmediateBlock* immediateBlock;
	InvBlock* invBlock;
	ModBlock* modBlock;
	MulBlock* mulBlock;
	OrBlock* orBlock;
	ShlBlock* shlBlock;
	ShrBlock* shrBlock;
	SplitterBlock* splitterBlock;
	SubBlock* subBlock;
	XorBlock* xorBlock;
	LocalizedLabel* cipherToolsLabel;
	LocalizedLabel* numericLabel;
	LocalizedLabel* binaryOperatorsLabel;
	LocalizedLabel* basicOperatorsLabel;
	LocalizedLabel* specialLabel;

	std::vector<BlockBase*> numericBlocks;
	std::vector<BlockBase*> binaryOperatorBlocks;
	std::vector<BlockBase*> basicOperatorsBlocks;
	std::vector<BlockBase*> specialBlocks;
};
