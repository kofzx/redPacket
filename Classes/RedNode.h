#pragma once
#include "cocos2d.h"
USING_NS_CC;

class RedNode : public Node
{
public:
	RedNode();
	~RedNode();

	virtual bool init();

	CREATE_FUNC(RedNode);

	void loadAnimate();
	void playAnimate();
	void aniCallback();
	void setDefault();
	void addTitle(const char* text);
private:
	Animate* animate;
	Sprite* backImg;
	Label* title;
};

