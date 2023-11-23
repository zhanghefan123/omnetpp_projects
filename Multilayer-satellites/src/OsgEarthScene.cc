//
// This file is part of an OMNeT++/OMNEST simulation example.
//
// Copyright (C) 2015 OpenSim Ltd.
//
// This file is distributed WITHOUT ANY WARRANTY. See the file
// `license' for details on this and other legal matters.
//

#if defined(WITH_OSG) && defined(WITH_OSGEARTH)

#include "OsgEarthScene.h"
#include "ConstVars.h"
#include <osgDB/ReadFile>
#include <osg/PositionAttitudeTransform>
#include <osgEarth/MapNode>
#include <osgEarthAnnotation/RectangleNode>
#include <osgEarth/Version>
#if OSGEARTH_VERSION_GREATER_OR_EQUAL(2, 6, 0)
    #include <osgEarthUtil/Sky>
#else
    #include <osgEarthUtil/SkyNode>
#endif

using namespace osgEarth;
using namespace osgEarth::Annotation;

Define_Module(OsgEarthScene);

OsgEarthScene *OsgEarthScene::instance = nullptr;

OsgEarthScene::OsgEarthScene() // NOLINT
{
    if (instance)
        throw cRuntimeError("There can be only one OsgEarthScene instance in the network"); // NOLINT
    instance = this;
}

OsgEarthScene::~OsgEarthScene()
{
    instance = nullptr;
}

void OsgEarthScene::initialize()
{
    // 从文件之中读取地球场景的数据，这个地球场景可能是通过某种文件格式描述的，例如地理信息系统（GIS）数据文件。
    auto mapNode = dynamic_cast<osgEarth::MapNode*>(osgDB::readNodeFile(par(inet::PAR_EARTH_SCENE.c_str())));

    // 检查是否成功加载
    if (!mapNode)
        throw cRuntimeError("Could not read scene file \"%s\"", par(inet::PAR_EARTH_SCENE.c_str()).stringValue()); // NOLINT

    // 获取父模块的 OSG 画布
    cOsgCanvas *builtinOsgCanvas = getParentModule()->getOsgCanvas();

    // 设置 OSG 画布的相机操作类型为轨迹球，允许用户通过鼠标交互旋转，平移以及缩放场景
    builtinOsgCanvas->setCameraManipulatorType(cOsgCanvas::CAM_TRACKBALL);

    // 设置OSG画布的查看器风格为地球风格，这可能会调整相机和其他参数以适应地球场景。
    builtinOsgCanvas->setViewerStyle(cOsgCanvas::STYLE_EARTH);

    // 设置OSG画布的清除颜色为黑色，这是场景背景的颜色。
    builtinOsgCanvas->setClearColor(cOsgCanvas::Color("black"));

    // 设置相机的近剪裁面和远剪裁面的距离，以定义可见场景的范围。
    builtinOsgCanvas->setZNear(1000000);
    builtinOsgCanvas->setZFar(100000000);

    // 创建一个osg::PositionAttitudeTransform对象，该对象用于控制地球场景的位置和方向
    earthRotator = new osg::PositionAttitudeTransform();

    // 并将之前加载的mapNode作为子节点添加到该变换中。
    earthRotator->addChild(mapNode);

    // 创建一个osg::Group对象，将前面创建的earthRotator添加为子节点。
    scene = new osg::Group();
    scene->asGroup()->addChild(earthRotator);


    #if OSGEARTH_VERSION_GREATER_OR_EQUAL(2, 6, 0)
        // 模拟地球的天空效果
        earthRotator->addChild(osgEarth::Util::SkyNode::create(mapNode));
    #else
        earthRotator->addChild(new osgEarth::Util::SkyNode(mapNode->getMap()));
    #endif

    // 设置OpenGL渲染状态，启用混合（blending），剔除（culling）和关闭光照。
    auto stateSet = scene->getOrCreateStateSet();
    stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
    stateSet->setMode(GL_CULL_FACE, osg::StateAttribute::ON);
    stateSet->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

    mapNode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::ON);

    // 将前面创建的场景设置为OSG画布的场景，使其可以在GUI中显示。
    builtinOsgCanvas->setScene(scene);

    // 设置模拟速度，将一小时的模拟时间映射到一秒的实际时间，以及设置动画的速度。这可能与模拟时间和实际时间的比例有关。
    getParentModule()->getCanvas()->setAnimationSpeed(360, this);
}

OsgEarthScene *OsgEarthScene::getInstance()
{
    if (!instance)
        throw cRuntimeError("OsgEarthScene::getInstance(): there is no OsgEarthScene module in the network"); // NOLINT
    return instance;
}

void OsgEarthScene::refreshDisplay() const
{
    double angle = double(simTime().inUnit(SIMTIME_S)) / 60.0 / 60 / 24 * 2 * M_PI;
    earthRotator->setAttitude(osg::Quat(angle, osg::Vec3d(0, 0, 1)));
}
#endif // WITH_OSG
