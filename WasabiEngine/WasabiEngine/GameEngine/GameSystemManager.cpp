/* 
 * File:   GameSystemManager.cpp
 * Author: fran
 * 
 * Created on 22 de noviembre de 2010, 16:56
 */

#include "GameSystemManager.h"
#include <WasabiEngine/GameEngine/GameLoop.h>

using namespace WasabiEngine;

GameSystemManager::GameSystemManager() {
    //Starts SDL
    if (SDL_Init(0) < 0) {
        fprintf(stderr, "Unable to initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    //Starts GraphicEngine
    //It should be started before EventEngine
    GraphicEngine::getInstance();
    //Starts EventEngine
    EventEngine::getInstance();
    quitHandlerRegistration = NULL;
    gameLoop = NULL;
}

GameSystemManager::GameSystemManager(const GameSystemManager& orig) {
    //FIXME: Deberia ser singleton
}

GameSystemManager::~GameSystemManager() {
    if (quitHandler != NULL)
        delete quitHandler;
    finishSystem();
}

void GameSystemManager::setGameLoop(GameLoop* gameLoop) {
    if (quitHandlerRegistration != NULL) {
        quitHandlerRegistration->removeHandler();
        delete quitHandler;
    }

    quitHandler = new QuitHandler(gameLoop);
    quitHandlerRegistration = EventEngine::getInstance()->addHandler(quitHandler, true);

    this->gameLoop = gameLoop;
    gameLoop->gameSystemManager = this;
}

bool GameSystemManager::initSystem() {
    return true;
}

bool GameSystemManager::finishSystem() {
    delete PhysicEngine::getInstance();
    SDL_Quit();
    return true;
}

void GameSystemManager::setVideoMode(const GraphicEngineConf& conf) {
    GraphicEngine::getInstance()->setVideoMode(conf);
}

void GameSystemManager::run() {
    gameLoop->run();
}