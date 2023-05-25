#include "Scene_040_GameOfLife.h"

#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_040_GameOfLife::Scene_040_GameOfLife() {

}

Scene_040_GameOfLife::~Scene_040_GameOfLife() {
    clean();
}

void Scene_040_GameOfLife::setGame(Game *_game) {
    game = _game;
}

void Scene_040_GameOfLife::load() {
    Assets::loadComputeShader(SHADER_COMP(SHADER_NAME), SHADER_ID(SHADER_NAME));
    cShader = Assets::getComputeShader(SHADER_ID(SHADER_NAME));

    /*
    MORE SHADER CODE
    */
}

void Scene_040_GameOfLife::clean() {
}
void Scene_040_GameOfLife::pause() {
}
void Scene_040_GameOfLife::resume() {
}
void Scene_040_GameOfLife::handleEvent(const InputState &inputState) {
}

void Scene_040_GameOfLife::update(float dt) {
    /*
    MORE SHADER CODE
    */
}

void Scene_040_GameOfLife::draw() {

}

int Scene_040_GameOfLife::randomInt() {
    static unsigned int seed = 0x13371337;

    int res;
    unsigned int tmp;

    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1);
}