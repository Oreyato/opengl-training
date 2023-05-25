#include "Scene_040_GameOfLife.h"

#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_040_GameOfLife::Scene_040_GameOfLife() :
    frameIndex{ 0 } 
{

}

Scene_040_GameOfLife::~Scene_040_GameOfLife() {
    clean();
}

void Scene_040_GameOfLife::setGame(Game *_game) {
    game = _game;
}

void Scene_040_GameOfLife::load() {
    Assets::loadComputeShader(SHADER_COMP(SHADER_NAME), SHADER_ID(SHADER_NAME));
    computeShader = Assets::getComputeShader(SHADER_ID(SHADER_NAME));

    static const Vector2 geometry[] = {
        // Positions
        Vector2(-1.0f, -1.0f),
        Vector2(-1.0f,  1.0f),
        Vector2( 1.0f, -1.0f),
        Vector2( 1.0f,  1.0f)
    };

    glGenBuffers(2, dataBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dataBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_ELEMENTS * sizeof(bool), NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dataBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_ELEMENTS * sizeof(bool), NULL, GL_DYNAMIC_COPY);

    // Geom shader
    //

    // Attribute pointers
    //

    glBindBuffer(GL_ARRAY_BUFFER, dataBuffer[0]);
    bool* ptr = reinterpret_cast<bool *>(
                        glMapBufferRange(
                            GL_ARRAY_BUFFER, 0, NUM_ELEMENTS * sizeof(bool), 
                            GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
                        )
    );

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        ptr[i] = randomBool();
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
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
    computeShader.use();

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[frameIndex]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, dataBuffer[frameIndex ^ 1]);

    glDispatchCompute(NUM_ELEMENTS, 1, 1);
}

void Scene_040_GameOfLife::draw() {


    frameIndex ^= 1;
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

bool Scene_040_GameOfLife::randomBool() {
    int i = randomInt();

    if (i % 2 == 0) {
        return false;
    } else return true;
}