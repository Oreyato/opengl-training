#include "Scene_030_Test.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_030_Test::Scene_030_Test(): totalTime(0) {

}

Scene_030_Test::~Scene_030_Test() {
    clean();
}

void Scene_030_Test::setGame(Game *_game) {
    game = _game;
}

void Scene_030_Test::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_030_Test::pause() {
}

void Scene_030_Test::resume() {
}

void Scene_030_Test::handleEvent(const InputState &inputState) {

}

void Scene_030_Test::load() {
    if (tesselation) {
        Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));
    }
    else {
        Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));
    }

    static const GLfloat tetrahedron_verts[] =
    {
         0.000f,  0.000f,  1.000f,
         0.943f,  0.000f, -0.333f,
        -0.471f,  0.816f, -0.333f,
        -0.471f, -0.816f, -0.333f
    };

    static const GLushort tetrahedron_indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 1,
        3, 2, 1
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer); // GL_ELEMENT_ARRAY_BUFFER = vertex array indices
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_verts) + sizeof(tetrahedron_indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(tetrahedron_indices), tetrahedron_indices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_indices), sizeof(tetrahedron_verts), tetrahedron_verts);

    glBindBuffer(GL_ARRAY_BUFFER, buffer); // GL_ARRAY_BUFFER = vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(tetrahedron_indices)); // Define an array of generic vertex attributes data
    glEnableVertexAttribArray(0);

    // glEnable(GL_CULL_FACE);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glPatchParameteri(GL_PATCH_VERTICES, 3);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // GL_POINT  GL_LINE  GL_FILL

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_030_Test::update(float dt) {
    totalTime += dt;
}

void Scene_030_Test::draw()
{
    // Variables init =======================
    static const GLfloat blue[] = {0.05f, 0.25f, 0.45f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = totalTime * timeScale;

    // Variables update =====================
    innerLength = (abs(sin(f)) + 1.0f) * 2.0f;
    innerWidth = (abs(sin(f)) + 1.0f) * 2.0f;
    outerWidth = (abs(sin(f)) + 1.0f) * 2.0f;
    outerLength = (abs(sin(f)) + 1.0f) * 2.0f;

    // Buffer clear =========================
    glClearBufferfv(GL_COLOR, 0, blue);
    glClearBufferfv(GL_DEPTH, 0, &one);

    // Projections ==========================
    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -8.0f)) *
                            Matrix4::createRotationY(f * 20.0f) *
                            Matrix4::createRotationX(f * 0.0f)
    ;

    shader.use();
    // Update tesselation control shader ====

    shader.setFloat("innerLength", innerLength);
    shader.setFloat("innerWidth", innerWidth);
    shader.setFloat("outerWidth", outerWidth);
    shader.setFloat("outerLength", outerLength);

    shader.setFloat("inner", innerWidth);
    shader.setFloat("outer", outerWidth);

    // Update geometry shader ===============

    shader.setMatrix4("mvpMatrix", proj * view);
    shader.setMatrix4("mvMatrix", view);
    shader.setFloat("stretch", sinf(f * 4.0f) * 0.75f + 1.0f);

    glPointSize(5.0f);
    glDrawElements(GL_PATCHES, 12, GL_UNSIGNED_SHORT, NULL);
}
