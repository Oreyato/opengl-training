#ifndef Scene_Snake_H
#define Scene_Snake_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

class Scene_Snake : public Scene {
public:
    Scene_Snake();
    ~Scene_Snake();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
    GLuint vao;
    GLuint buffer;
    Matrix4 transform[24];
    Matrix4 projection;

    Shader shader;
};

#endif //Scene_Snake_H
