/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#pragma execution_character_set("utf-8")

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

HelloWorld::HelloWorld() {
	backImg = 0;
	state = 0;
}
HelloWorld::~HelloWorld() {
	backImg = 0;
	state = 0;
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [=](Touch* touch, Event* event) {
		if (state == 0) {
			Vec2 touchPoint = touch->getLocation();
			Size s = redNode->getContentSize();
			Rect rect = Rect(redNode->getPositionX(),redNode->getPositionY(),s.width,s.height);
			if (rect.containsPoint(touchPoint)) {
				state = 1;
				unscheduleUpdate();
				redNode->setPosition(visibleSize.width/2, visibleSize.height/2);
				redNode->playAnimate();
				return true;
			}
		}
		else {
			state = 0;
			redNode->setDefault();
			scheduleUpdate();
		}

		return false;
	};

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

    auto item = MenuItemFont::create("ÇÀ",CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
	item->setFontSizeObj(120);
	item->setColor(Color3B::RED);

    // create menu, it's an autorelease object
    auto menu = Menu::create(item, NULL);
    menu->setPosition(visibleSize/2);
    this->addChild(menu, 1);

	setBackground("res/Background.jpg");

	redNode = RedNode::create();
	redNode->loadAnimate();
	redNode->setVisible(true);
	this->addChild(redNode, 1);
    
    return true;
}
void HelloWorld::update(float dt) {
	static float time = 0;
	if (time > 1.0f) {
		time = 0;
	}
	else {
		time += dt;
		return;
	}
	float pos_x = std::rand() % 720;
	float pos_y = std::rand() % 960;
	redNode->setVisible(true);
	redNode->setPosition(Vec2(pos_x,pos_y));

}
void HelloWorld::setBackground(const char* filename) {
	if (backImg == 0) {
		backImg = Sprite::create(filename);
		backImg->setAnchorPoint(Point::ZERO);
		backImg->setPosition(Point::ZERO);
		this->addChild(backImg);
		return;
	}
	backImg->setTexture(filename);
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
	static_cast<Node*>(pSender)->setVisible(false);
	scheduleUpdate();
    //Close the cocos2d-x game scene and quit the application
    //Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
