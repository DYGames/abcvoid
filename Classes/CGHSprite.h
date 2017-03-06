#pragma once

#include "cocos2d.h"

namespace GH 
{
	class CGHSprite : public cocos2d::Sprite
	{
	public:
		CGHSprite();
		virtual ~CGHSprite();

		virtual bool initWithFile(const std::string &filename);
		virtual bool initWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
	};

	class CGHSpriteBatchNode : public cocos2d::SpriteBatchNode
	{
	public:
		CGHSpriteBatchNode();
		virtual ~CGHSpriteBatchNode();

		virtual bool initWithFile(const std::string &filename , ssize_t capacity);
	};
}