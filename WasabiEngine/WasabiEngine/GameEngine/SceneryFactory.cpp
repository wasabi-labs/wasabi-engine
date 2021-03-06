/* 
 * File:   SceneryFactory.cpp
 * Author: Roberto
 * 
 * Created on 10 de enero de 2011, 23:33
 */

#include "SceneryFactory.h"

using namespace WasabiEngine;

SceneryFactory::SceneryFactory() {
    factory = new ResourceFactory<Scenery > ();
}

SceneryFactory::SceneryFactory(const unsigned int& nSceneries) {
    factory = new ResourceFactory<Scenery > (nSceneries);
}

SceneryFactory::SceneryFactory(const SceneryFactory& orig) {
    //Not allowed
}

SceneryFactory::~SceneryFactory() {
    clear();
    delete factory;
}

Scenery* SceneryFactory::create(const SceneryDefinition& definition) {
    Scenery* scenery = factory->createResource();
    PhysicObject* physicObj = NULL;
    GraphicObject* graphicObj = NULL;

    PhysicBodyDef bodyDef;
    bodyDef.bodyType = definition.physicBodyType;
    bodyDef.shapeType = PHYSIC_BOX_SHAPE;
    bodyDef.box.height = definition.length;
    bodyDef.box.width = definition.width;
    bodyDef.mass = definition.mass;
    bodyDef.friction = 1.2; //FIXME: Mirar que hago con esto.
    bodyDef.position = definition.position;
    bodyDef.rotation = definition.rotation;
    bodyDef.awake = false;
    physicObj = PhysicEngine::getInstance()->createObject(scenery->getId());
    physicObj->createBody("mainBody", bodyDef);

    if (definition.meshFile.length() > 0) {
        graphicObj = GraphicEngine::getInstance()->createObject(scenery->getId());
        graphicObj->createEntity(definition.meshFile);
    }
    
    return scenery;
}

void SceneryFactory::destroy(Scenery* scenery) {
    PhysicObject* physic = PhysicEngine::getInstance()->getItem(scenery->getId());
    GraphicObject* graphic = GraphicEngine::getInstance()->getItem(scenery->getId());
    if(physic)
        PhysicEngine::getInstance()->destroyObject(physic);
    if(graphic)
        GraphicEngine::getInstance()->destroyObject(graphic);
    factory->returnResource(scenery);
//    if (factory->returnResource(scenery)) {
//        PhysicEngine::getInstance()->destroyObject(PhysicEngine::getInstance()->getItem(scenery->getId()));
//        GraphicEngine::getInstance()->destroyObject(GraphicEngine::getInstance()->getItem(scenery->getId()));
//    }
}

void SceneryFactory::clear() {
    std::set<Scenery*>& scenery = factory->getResources();
    while(!scenery.empty())
        destroy(*scenery.begin());
//    for (std::set<Scenery*>::iterator i = factory->getResources().begin(); i != factory->getResources().end(); i++) {
//        destroy(*i);
//    }
}
