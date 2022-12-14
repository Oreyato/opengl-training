//
// Created by gaetz on 04/12/2019.
//

#include "Scene_005_Tessellation.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_005_Tessellation::Scene_005_Tessellation() {
}

Scene_005_Tessellation::~Scene_005_Tessellation() {
    clean();
}

void Scene_005_Tessellation::setGame(Game *_game) {
    game = _game;
}

void Scene_005_Tessellation::load() {
    std::srand((int) std::time(nullptr));

    Assets::loadShader("assets/shaders/005_tessellation.vert", "assets/shaders/005_tessellation.frag",
                                "assets/shaders/005_tessellation.tesc", "assets/shaders/005_tessellation.tese",
                                "", "005_tessellation"
    );

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader = Assets::getShader("005_tessellation");
}

void Scene_005_Tessellation::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_005_Tessellation::pause() {
}

void Scene_005_Tessellation::resume() {
}

void Scene_005_Tessellation::handleEvent(const InputState &inputState) {
}

void Scene_005_Tessellation::update(float dt) {
    float timeValue = (float)SDL_GetTicks()/1000;

    innerVal = (abs(sin(timeValue))) * 15.0f;
    outerVal = (abs(sin(timeValue))) * 15.0f;

    std::cout << innerVal << " : " << outerVal << std::endl;
}

void Scene_005_Tessellation::draw() {
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();

    shader.setFloat("inner", innerVal);
    shader.setFloat("outer", outerVal);

    glPointSize(5.0f);

    glDrawArrays(GL_PATCHES, 0, 4);
}
