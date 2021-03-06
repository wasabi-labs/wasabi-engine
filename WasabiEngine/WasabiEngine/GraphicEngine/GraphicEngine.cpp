/* 
 * File:   GraphicEngine.cpp
 * Author: fran
 * 
 * Created on 21 de noviembre de 2010, 17:10
 */


#include "GraphicEngine.h"

using namespace WasabiEngine;

GraphicEngine::GraphicEngine() {
}

GraphicEngine::GraphicEngine(const GraphicEngine& orig) {
    //Not allowed
}

GraphicEngine::~GraphicEngine() {
}

void GraphicEngine::setVideoMode(const GraphicEngineConf& conf) {
    sceneManager.renderSystem.setVideoMode(conf);
}

GraphicEngineConf GraphicEngine::getGraphicEngineConfig() const{
    return sceneManager.renderSystem.getGraphicEngineConfig();
}

void GraphicEngine::setWorldGeometry(const std::string& filePath) {
    sceneManager.setWorldGeometry(filePath);
}

void GraphicEngine::setAmbientLight(const ColourValue& colour, const WasVec3d& position) {
    sceneManager.setAmbientLight(colour, position);
}

LightPoint* GraphicEngine::createLightPoint() {
    return sceneManager.createLightPoint();
}

SpotLight* GraphicEngine::createSpotLight() {
    return sceneManager.createSpotLight();
}

void GraphicEngine::destroyLight(Light* light) {
    sceneManager.destroyLight(light);
}

void GraphicEngine::render() {
    sceneManager.render();
}

GraphicObject* GraphicEngine::createObject(const int& id) {
    GraphicObject* object = objectFactory.createResource();
    object->setId(id);
    object->prepare();
    propertyMap.set(id, object);
    return object;
}

void GraphicEngine::destroyObject(GraphicObject* object) {
    propertyMap.remove(object->getId());
    objectFactory.returnResource(object);
}

Camera* GraphicEngine::createCamera(const std::string& name) {
    return sceneManager.createCamera(name);
}

void GraphicEngine::destroyCamera(Camera* camera) {
    sceneManager.destroyCamera(camera);
}

void GraphicEngine::destroyCamera(const std::string& name) {
    sceneManager.destroyCamera(name);
}

Camera* GraphicEngine::getActiveCamera() {
    return sceneManager.getActiveCamera();
}

void GraphicEngine::setActiveCamera(Camera* camera) {
    sceneManager.setActiveCamera(camera);
}

void GraphicEngine::setActiveCamera(const std::string& name) {
    sceneManager.setActiveCamera(name);
}

Camera* GraphicEngine::getCamera(const std::string& name) {
    return sceneManager.getCamera(name);
}

void GraphicEngine::init() {
    /* Initialize SDL for video output. Watch out! It needs that SDL_Init() has been called first */
    if (SDL_InitSubSystem(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    // Initialize SDL image formats to support
    int flags = IMG_INIT_JPG | IMG_INIT_PNG;
    int initted = IMG_Init(flags);
    if ((initted & flags) != flags) {
        fprintf(stderr, "IMG_Init: Failed to init required jpg and png support!\n");
        fprintf(stderr, "IMG_Init: %s\n", IMG_GetError());
    }

    GraphicEngineConf defaultConf;
    defaultConf.width = 640;
    defaultConf.height = 480;
    defaultConf.fullscreen = false;
    defaultConf.wmCaption = "WasabiEngine";
    setVideoMode(defaultConf);

    sceneManager.reserveLightMemory();

    /* Initialize CEGUI */
    CEGUISystem::getInstance()->init();
}

void GraphicEngine::finish() {
    TextureLoader::unloadAll();
    MeshMap::unloadAll();
    destroyObjects();
    CEGUISystem::getInstance()->finish();
    SDL_QuitSubSystem(SDL_INIT_VIDEO);
}

void GraphicEngine::destroyObjects() {
    std::list<GraphicObject*> graphicObjects = propertyMap.getItems();
    std::list<GraphicObject*>::iterator it;
    for (it = graphicObjects.begin(); it != graphicObjects.end(); it++)
        destroyObject(*(it));
}
