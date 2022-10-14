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

    //v Load snake and apples ===============================
    // Snake parts
    snake = new Snake(0.0f, 0.0f, maxDepth, 1.0f, 0.5f, 1.0f, 4.0f, cubeMesh, cubeMesh);

    // Apples
    apples.emplace_back(.0f, .0f, maxDepth, cubeMesh, .5f, 125.0f);
    apples.emplace_back(2.0f, 2.0f, maxDepth, cubeMesh, 1.0f);
    //^ Load snake and apples ===============================
}

void Scene_Snake::clean() {
    cubeMesh->clean();
    delete cubeMesh;

    delete snake;
}

void Scene_Snake::pause() {
}

void Scene_Snake::resume() {
}

void Scene_Snake::handleEvent(const InputState &inputState) {
}

void Scene_Snake::update(float dt) {

    // Ref this code with a pointer to only use one loop
    for (auto& cube : cubes)
    {
        cube.update();
    }
    for (auto& apple : apples)
    {
        apple.update();
    }
}

void Scene_Snake::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);

    snake->draw(shader);

    for (auto& cube : cubes)
    {
        cube.draw(shader);
    }
    for (auto& apple : apples)
    {
        apple.draw(shader);
    }
    
        
}