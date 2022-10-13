#include "Scene_Snake.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

#include "CubeMesh.h"

Scene_Snake::Scene_Snake() {
}

Scene_Snake::~Scene_Snake() {
    clean();
}

void Scene_Snake::setGame(Game *_game) {
    game = _game;
}

void Scene_Snake::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    cubeMesh = new CubeMesh();
    cubeMesh->load();

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));



    cubes.emplace_back(0.0f, -.5f, maxDepth, cubeMesh, 0.5f);
    cubes.emplace_back(1.0f, 0.0f, maxDepth, cubeMesh);
    cubes.emplace_back(-1.0f, 0.0f, maxDepth, cubeMesh, 2.0f);
    cubes.emplace_back(0.0f, -1.0f, maxDepth, cubeMesh, 1.5f);

    apples.emplace_back(.0f, .0f, maxDepth, cubeMesh, .5f, 125.0f);
    apples.emplace_back(2.0f, 2.0f, maxDepth, cubeMesh, 1.0f);
}

void Scene_Snake::clean() {
    cubeMesh->clean();
    delete cubeMesh;
}

void Scene_Snake::pause() {
}

void Scene_Snake::resume() {
}

void Scene_Snake::handleEvent(const InputState &inputState) {
}

void Scene_Snake::update(float dt) {
    for (auto& cube : cubes)
    {
        cube.update();
    }

    for (auto& apple : apples)
    {
        apple.update();
    }
    

    // // Update snake body
    // for(int i = 0; i < snakeBodyCount; ++i)
    // {
    //     const float t = i + Timer::getTimeSinceStart() * 0.3f;
    //     transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
    //         * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
    //         * Matrix4::createRotationX(t * Maths::toRadians(21.0f))
    //         * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 2.0f, 
    //                                              Maths::cos(1.7f * t) * 2.0f, 
    //                                              Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    // }
    // // Update apple
    // for(int i = snakeBodyCount; i < snakeBodyCount + appleCount; ++i)
    // {
    //     const float t = i + Timer::getTimeSinceStart() * 0.3f;
    //     transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
    //         * Matrix4::createRotationX(t * Maths::toRadians(20.0f));
    //         //* Matrix4::createTranslation(Vector3(0.0f, 0.0f, Maths::cos(0.5 * t) * 2.0f));
    //     }
}

void Scene_Snake::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    // // Draw snake body
    // for(int i = 0; i < snakeBodyCount; ++i)
    // {
    //     shader.setMatrix4("mv_matrix", transform[i]);
    //     cube.draw(shader);
    // }
    // // Draw apple
    // for(int i = snakeBodyCount; i < snakeBodyCount + appleCount; ++i)
    // {
    //     shader.setMatrix4("mv_matrix", transform[i]);
    //     cube.draw();
    // }
    for (auto& cube : cubes)
    {
        cube.draw(shader);
    }

    for (auto& apple : apples)
    {
        apple.draw(shader);
    }
    
    
}