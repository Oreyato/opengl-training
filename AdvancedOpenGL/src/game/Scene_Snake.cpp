#include "Scene_Snake.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

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

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    //projection = Matrix4::createOrtho(game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    
    cube.load();

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_Snake::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_Snake::pause() {
}

void Scene_Snake::resume() {
}

void Scene_Snake::handleEvent(const InputState &inputState) {
}

void Scene_Snake::update(float dt) {
    // Update snake body
    for(int i = 0; i < snakeBodyCount; ++i)
    {
        const float t = i + Timer::getTimeSinceStart() * 0.3f;
        transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
            * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
            * Matrix4::createRotationX(t * Maths::toRadians(21.0f))
            * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 2.0f, 
                                                 Maths::cos(1.7f * t) * 2.0f, 
                                                 Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    }
    // Update apple
    for(int i = snakeBodyCount; i < snakeBodyCount + appleCount; ++i)
    {
        const float t = i + Timer::getTimeSinceStart() * 0.3f;
        transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
            * Matrix4::createRotationX(t * Maths::toRadians(20.0f));
            //* Matrix4::createTranslation(Vector3(0.0f, 0.0f, Maths::cos(0.5 * t) * 2.0f));
        }
}

void Scene_Snake::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    // Draw snake body
    for(int i = 0; i < snakeBodyCount; ++i)
    {
        shader.setMatrix4("mv_matrix", transform[i]);
        cube.draw();
    }
    // Draw apple
    for(int i = snakeBodyCount; i < snakeBodyCount + appleCount; ++i)
    {
        shader.setMatrix4("mv_matrix", transform[j]);
        cube.draw();
    }
}