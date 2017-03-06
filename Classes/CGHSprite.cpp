#include "CGHSprite.h"

namespace GH
{
	CGHSprite::CGHSprite()
	{

	}

	CGHSprite::~CGHSprite()
	{

	}

	bool CGHSprite::initWithFile(const std::string &filename)
	{
		return Sprite::initWithFile(filename);
	}
	
	bool CGHSprite::initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame)
	{
		return Sprite::initWithSpriteFrame(spriteFrame);
	}
	////////////////////////////////////////////////////////

	CGHSpriteBatchNode::CGHSpriteBatchNode()
	{

	}

	CGHSpriteBatchNode::~CGHSpriteBatchNode()
	{

	}

	bool CGHSpriteBatchNode::initWithFile(const std::string &filename , ssize_t capacity)
	{
		return SpriteBatchNode::initWithFile(filename, capacity);
	}
}