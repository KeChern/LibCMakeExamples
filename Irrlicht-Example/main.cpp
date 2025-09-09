#include <irrlicht.h>

using namespace irr;

int main()
{
    // 创建 Irrlicht 设备
    IrrlichtDevice *device = createDevice(video::EDT_OPENGL,
                                          core::dimension2d<u32>(800, 600),
                                          16,
                                          false,
                                          false,
                                          false,
                                          0);
    if (!device) return 1;

    device->setWindowCaption(L"Irrlicht Demo: Centered Slow Cube");

    video::IVideoDriver* driver = device->getVideoDriver();
    scene::ISceneManager* smgr = device->getSceneManager();

    // 添加普通摄像机，不捕获鼠标
    scene::ICameraSceneNode* camera = smgr->addCameraSceneNode(
        0,                                // 父节点
        core::vector3df(0, 0, -40),       // 摄像机位置
        core::vector3df(0, 0, 0)          // 目标位置（正对立方体）
    );

    // 显示光标
    device->getCursorControl()->setVisible(true);

    // 添加旋转立方体，放在世界原点，即屏幕正中间
    scene::ISceneNode* cube = smgr->addCubeSceneNode(10.0f);
    if (cube) {
        cube->setPosition(core::vector3df(0, 0, 0));
        cube->setMaterialFlag(video::EMF_LIGHTING, true);
    }

    // 添加光源
    smgr->addLightSceneNode(0, core::vector3df(0,50,0),
                            video::SColorf(1.0f,1.0f,1.0f,1.0f), 800.0f);

    // 渲染循环
    while(device->run())
    {
        // 慢速旋转立方体
        cube->setRotation(cube->getRotation() + core::vector3df(0.1f, 0.2f, 0));

        driver->beginScene(true, true, video::SColor(255,100,101,140));
        smgr->drawAll();
        driver->endScene();
    }

    device->drop();
    return 0;
}
