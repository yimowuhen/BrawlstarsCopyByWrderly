 //修改 : 李元特
 //日期 : 2022-5-18

#include "AppDelegate.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(960, 720);
static cocos2d::Size smallResolutionSize = cocos2d::Size(960, 720);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(960, 720);
static cocos2d::Size largeResolutionSize = cocos2d::Size(960, 720);
/**
static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);
/**/
AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Brawlstars", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Brawlstars");
#endif
        glview->setFrameSize(960, 720);
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);

    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }

    register_all_packages();

    // create a scene. it's an autorelease object
    auto scene = MainMenuScene::createScene();

    // run
    director->runWithScene(scene);

    //初始化 音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/retro_fight_ingame_01.mp3");
    // 游戏中的音乐
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music/first_music.mp3");
    // 进入游戏menu的音乐


    //初始化 音效
    SimpleAudioEngine::getInstance()->preloadEffect("sound/empty.wav");
    // 障碍物碰撞
    SimpleAudioEngine::getInstance()->preloadEffect("music/start_game_music.mp3");
    // 设想在做一个初识进入游戏的界面

    SimpleAudioEngine::getInstance()->preloadEffect("music/if_hero_kill_monster.mp3");
    // 玩家战胜一只怪兽
    SimpleAudioEngine::getInstance()->preloadEffect("music/if_click_buttom_on_menu.mp3");
    // 点设置按钮

    // 一下都和技能有关
    SimpleAudioEngine::getInstance()->preloadEffect("music/gun_skill_3times.wav");
    SimpleAudioEngine::getInstance()->preloadEffect("music/gun_attack.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("music/laser_skill.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("music/laser_attack.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_2.mp3");
    SimpleAudioEngine::getInstance()->preloadEffect("music/knife_attack_1.mp3");





    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // 暂停音乐（SimpleAudioEngine）
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic(); //attached


#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // 恢复音乐（SimpleAudioEngine）
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();//attached



#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
