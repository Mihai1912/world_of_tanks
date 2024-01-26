#pragma once

#include "EnemyTank.h"
#include "components/simple_scene.h"
#include "lab_m1/tema2/Camera.h"
#include "lab_m1/tema2/Tank.h"
#include "lab_m1/tema2/Building.h"


namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

        Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);
        
    
    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color , float health);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderTank();
        void MoveProjectile(float deltaTimeSeconds);

        void RenderBuildings();

        bool CheckCollisionTankBuildings(float deltaTime);
        bool CheckCollisionProjectileBuildings(float deltaTime , Projetile *projectile);
        bool CheckCollisionProjectileTank(float deltaTime , Projetile& projectile);
        bool CheckCollisionTankEnemyTanks(float deltaTime);
        bool CheckEnemyProjectileMyTank(float deltaTime , Projetile& projectile);
        bool CheckCollisionEnemyTanksBuildings(float deltaTime , EnemyTank& enemyTank);

        void RenderEnemyTanks(float deltaTime);
        void ChangeEnemyTanksDirection(float deltaTime);
        void MoveEnemyTanks(float deltaTime , EnemyTank *enemyTank);

        void CheckEnemyTanksShoot(float deltaTime);
        void EnemyTanksShoot(float deltaTime);

        void EnemyTanksShootPlayer(float deltaTime);
        
        
    protected:
        implemented::CameraT2 *camera;
        glm::mat4 projectionMatrix;

        // TODO(student): If you need any other class variables, define them here.

        float initalclock = 0;
        float clock = 0;

        float FOV = RADIANS(60);
        float bottom = -10.0f;
        float top = 10.0f;

        float angle = 0;

        glm::vec3 lightPosition;
        unsigned int materialShininess;
        float materialKd;
        float materialKs;

        Tank *myTank;

        std::vector<Building> buildings;

        std::vector<EnemyTank> enemyTanks;

        std::vector<std::tuple<int , int>> circle;
    };
}   // namespace m1
