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
    // bool* ptr = reinterpret_cast<bool *>(
    //                     glMapBufferRange(
    //                         GL_ARRAY_BUFFER, 0, NUM_ELEMENTS * sizeof(bool), 
    //                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT
    //                     )
    // );

    for (int i = 0; i < NUM_ELEMENTS; i++) {
        inputData[i] = randomBool();
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    int n;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &n);

    glShaderStorageBlockBinding(computeShader.id, 0, 0);
    glShaderStorageBlockBinding(computeShader.id, 1, 1);

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
    bool* ptr{ nullptr };

    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[frameIndex]);
    // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, dataBuffer[frameIndex ^ 1]);

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[0], 0, sizeof(bool) * NUM_ELEMENTS);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(bool) * NUM_ELEMENTS, inputData);

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, dataBuffer[1], 0, sizeof(bool) * NUM_ELEMENTS);

    computeShader.use();
    glDispatchCompute(NUM_ELEMENTS, 1, 1);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    // glFinish();

    bool* data = new bool[NUM_ELEMENTS];
    glGetBufferSubData(GL_SHADER_STORAGE_BUFFER, 1, sizeof(bool) * NUM_ELEMENTS, data);

    // glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[1], 0, sizeof(bool) * NUM_ELEMENTS);
    // ptr = (bool*)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(bool) * NUM_ELEMENTS, GL_MAP_READ_BIT);

    // const int bufferSize = NUM_ELEMENTS / 2;
    // char buffer[bufferSize];
    // sprintf(buffer, 
    //     "LIFE: %i %i %i %i %i", 
    //         ptr[0], ptr[1], ptr[2], ptr[3], ptr[4]
    // );

    for (int i = 0; i < 25; i++) {
        LOG(Info) << data[i];
    }

    //glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
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