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
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_W)) {
        wireframe = !wireframe;
    }
}

void Scene_030_Test::load() {
    if (tesselation) {
        Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));
    }
    else {
        Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat vertexPositions[] =
    {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    if (wallpaper) {
        glDisable(GL_CULL_FACE);
    }
    else {
        glEnable(GL_CULL_FACE);
        glCullFace(GL_CW); // GL_BACK
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    
    glPatchParameteri(GL_PATCH_VERTICES, 3);

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
    float div = (sinf(f) + 1.0f) * (innerMaxValue - 1.0f) - (innerMaxValue - 1.0f); 
    inner = abs(div) + 1.0f; // Clamp inner between 1 and its max value
    outer = abs((sinf(f) + 1.0f) * (outerMaxValue - 1.0f) - (outerMaxValue - 1.0f)) + 1.0f; // Clamp outer between 1 and its max value

    div /= 2.0f;
    std::cout << "outer: " << outer << " | div: " << div << std::endl;

    // Buffer clear =========================
    glClearBufferfv(GL_COLOR, 0, blue);
    glClearBufferfv(GL_DEPTH, 0, &one);

    // Projections ==========================
    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -2.0f)) *
                            Matrix4::createRotationX(f * 4.0f * div) *
                            Matrix4::createRotationY(f * 2.0f * div) *
                            Matrix4::createRotationZ(f * .0f) 
    ;

    shader.use();

    // Update vertex shader =================
    shader.setMatrix4("mv_matrix", view);
    shader.setMatrix4("proj_matrix", proj);

    // Update tesselation control shader ====
    shader.setFloat("inner", inner);
    shader.setFloat("outer", outer);

    // Update geometry shader ===============

    if (wallpaper) {
        shader.setMatrix4("mvpMatrix", proj);
    }
    else {
        shader.setMatrix4("mvpMatrix", proj * view);
    }
    shader.setMatrix4("mvMatrix", view);

    shader.setFloat("stretch", sinf(f * 4.0f) * 0.5f + 1.0001f);
                                   // ^frequency ^magnitude ^offset (to always have a value > 0)

    glPointSize(5.0f);

    // Actual draw ==========================
    if (tesselation) {
        int maxI = 6*6;
        for (int i = 0; i < maxI; i+=3)
        {
            glDrawArrays(GL_PATCHES, i, 3);
        }
    }
    else  {
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // GL_POINT  GL_LINE  GL_FILL
    } else {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
    }

    // glDrawElements(GL_PATCHES, 12, GL_UNSIGNED_SHORT, NULL);
}
