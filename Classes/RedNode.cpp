#pragma execution_character_set("utf-8")

#include "RedNode.h"

std::vector<std::string> context = {"°ÙÍò´ó½±","Ò»Ã«Ç®","Ð»Ð»»Ý¹Ë"};

RedNode::RedNode()
{
	backImg = 0;
	animate = 0;
	title = 0;
}


RedNode::~RedNode()
{
	backImg = 0;
	animate = 0;
	title = 0;
}

bool RedNode::init() {
	backImg = Sprite::create("res/default.png");
	backImg->setAnchorPoint(Point::ZERO);
	this->addChild(backImg);
	setContentSize(backImg->getContentSize());

	return true;
}
void RedNode::loadAnimate() {
	SpriteFrameCache* spriteFrameCache = SpriteFrameCache::getInstance();
	int index = 1;
	SpriteFrame* frame = NULL;
	Vector<SpriteFrame*> frameArray;

	do
	{
		frame = spriteFrameCache->getSpriteFrameByName(__String::createWithFormat("%d.png", index)->getCString());
		if (frame == 0) {
			break;
		}
		frameArray.pushBack(frame);
		index++;
	} while (true);

	Animation* animation = Animation::createWithSpriteFrames(frameArray);
	animation->setLoops(1);
	animation->setRestoreOriginalFrame(false);
	animation->setDelayPerUnit(0.1);
	animate = Animate::create(animation);
	animate->retain();
}
void RedNode::playAnimate() {
	if (backImg != 0 && animate != 0) {
		backImg->setAnchorPoint(Vec2(0.5,0.5));
		CallFunc* callFunc = CallFunc::create(CC_CALLBACK_0(RedNode::aniCallback, this));
		Sequence* seq = Sequence::create(animate, callFunc, NULL);
		backImg->runAction(seq);
	}
}
void RedNode::aniCallback() {
	std::string str = context[std::rand() % context.size()];
	log("%s",str.c_str());
	addTitle(str.c_str());
}
void RedNode::setDefault() {
	if (backImg != 0) {
		backImg->removeFromParent();
		backImg = Sprite::create("res/default.png");
		backImg->setAnchorPoint(Point::ZERO);
		this->addChild(backImg);
		if (title != 0) {
			title->setVisible(false);
		}
	}
}
void RedNode::addTitle(const char* text) {
	if (title == 0) {
		title = Label::createWithSystemFont(text, "", 40);
		title->setPosition(Point::ZERO);
		title->setColor(Color3B::RED);
		this->addChild(title, 1);
		return;
	}
	title->setString(text);
	title->setVisible(true);
}