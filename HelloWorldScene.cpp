#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

static CCSprite *janken_aite;
static CCAnimate *janken_anime_run;
static CCLabelTTF *lbl_dis;

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object

    // add Title Label
    CCLabelTTF *lbl_title = CCLabelTTF::create("じゃんけんゲーム", "HirakakuProN-W6", 30);
    lbl_title->setPosition(CCPointMake(origin.x+visibleSize.width/2,
    		origin.y+visibleSize.height - lbl_title->getContentSize().height));
    this->addChild(lbl_title);
    
    // add Aite Image
    janken_aite = CCSprite::create("goo.png");
    janken_aite->setScale(0.5f);
    janken_aite->setPosition(CCPointMake(origin.x + visibleSize.width/2,
    		origin.y + 2*visibleSize.height/3 - lbl_title->getContentSize().height/2));
    this->addChild(janken_aite);

    // set Janken Animation Sequence
    CCAnimation *janken_anime = CCAnimation::create();
    janken_anime->addSpriteFrameWithFileName("choki.png");
    janken_anime->addSpriteFrameWithFileName("par.png");
    janken_anime->addSpriteFrameWithFileName("goo.png");
    janken_anime->setDelayPerUnit(0.1f);
    janken_anime->setLoops(-1);
    janken_anime->setRestoreOriginalFrame(true);
    janken_anime_run = (CCAnimate*)CCSequence::create(CCAnimate::create(janken_anime), NULL);

    // Execute Animation
    janken_aite->runAction(janken_anime_run);

    // add Janken Button
    CCMenuItemImage *btn_goo = CCMenuItemImage::create(
    		"goo.png",
    		"goo.png",
    		this,
    		menu_selector(HelloWorld::pushGoo));
    CCMenuItemImage *btn_choki = CCMenuItemImage::create(
        		"choki.png",
        		"choki.png",
        		this,
        		menu_selector(HelloWorld::pushChoki));
    CCMenuItemImage *btn_par = CCMenuItemImage::create(
        		"par.png",
        		"par.png",
        		this,
        		menu_selector(HelloWorld::pushPar));
    
    // Change Item Scale
    btn_goo->setScale(0.5f);
    btn_choki->setScale(0.5f);
    btn_par->setScale(0.5f);
    
    // add Menu Item
    btn_goo->setPosition(CCPoint(origin.x + btn_goo->getContentSize().width/4 + visibleSize.width/2 - 150,
                                 origin.y + btn_goo->getContentSize().height/4 + visibleSize.height/4));
    btn_choki->setPosition(CCPoint(btn_goo->getPosition().x + btn_choki->getContentSize().width/2 + 5,
                                   origin.y + btn_choki->getContentSize().height/4 + visibleSize.height/4));
    btn_par->setPosition(CCPoint(btn_choki->getPosition().x + btn_par->getContentSize().width/2 + 5,
                                 origin.y + btn_choki->getContentSize().height/4 + visibleSize.height/4));
    
    CCMenu *btns = CCMenu::create(btn_goo, btn_choki, btn_par, NULL);
    btns->setPosition(CCPointZero);
    this->addChild(btns);

    // init rand
    srand((unsigned)time(NULL));

    // add result label
    lbl_dis = CCLabelTTF::create("", "HirakakuProN-W6", 30);
    lbl_dis->setPosition(CCPoint(origin.x + visibleSize.width/2,
    							janken_aite->getPositionY() - janken_aite->getContentSize().height/2));
    addChild(lbl_dis);

    return true;
}

void HelloWorld::procJanken(int i)
{
	// goo:1 choki:2 par:3

	int rnd = rand() % 3 + 1;
	bool win = false;
	bool aiko = false;
	if(rnd == 1){
		if(i == 1){
			aiko = true;
		} else if(i == 3){
			win = true;
		}
	} else if(rnd == 2){
		if(i == 2){
			aiko = true;
		} else if(i == 1){
			win = true;
		}
	} else if(rnd == 3){
		if(i == 3){
			aiko = true;
		} else if(i == 2){
			win = true;
		}
	}

	// Set Aite Image
	janken_aite->stopAllActions();
	if(rnd == 1){
		janken_aite->setTexture(CCTextureCache::sharedTextureCache()->addImage("goo.png"));
	} else if(rnd == 2){
		janken_aite->setTexture(CCTextureCache::sharedTextureCache()->addImage("choki.png"));
	} else if(rnd == 3){
		janken_aite->setTexture(CCTextureCache::sharedTextureCache()->addImage("par.png"));
	}

    // Judgement
	if(aiko){
		lbl_dis->setString("あいこでしょ！");
	}else{
		if(win){
			lbl_dis->setString("勝ち！");
		}else{
			lbl_dis->setString("負け！");
		}
	}
}

void HelloWorld::pushGoo(CCObject *pSender)
{
	this->procJanken(1);
}

void HelloWorld::pushChoki(CCObject *pSender)
{
	this->procJanken(2);
}

void HelloWorld::pushPar(CCObject *pSender)
{
	this->procJanken(3);
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
