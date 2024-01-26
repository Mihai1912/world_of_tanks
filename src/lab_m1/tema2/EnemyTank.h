#pragma once

#include <map>
#include <random>

#include "components/simple_scene.h"
#include "Projectile.h"
#include "MovementClass.h"


class EnemyTank : public gfxc::SimpleScene
{
public:
    EnemyTank()
    {
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        forward_turela = glm::vec3(0, 0, -1);
        turela_ang = 0;
        EnemyTank_ang = 0;
        color = glm::vec3(1,0,0);
    };
    
    ~EnemyTank() { };

    void Init(){
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        forward_turela = glm::vec3(0, 0, -1);
        turela_ang = 0;
        EnemyTank_ang = 0;
        color = glm::vec3(1,0,0);
    }

    void shoot (){
        Projetile *p = new Projetile();
        p->setPosition(position);
        p->setForward(forward_turela);
        p->setTurelaAngle(turela_ang);
        projectiles.push_back(*p);
    }

    std::vector<Projetile> projectiles;
    glm::vec3 position;
    float radius = 1.5f;
    
    float health = 3;
    
    glm::vec3 forward;
    glm::vec3 forward_turela;
    
    float turela_ang;
    float EnemyTank_ang;
    
    glm::vec3 color;
    
    MoveObject moveObject;
    float changeDirectionTime = 0;
    State currentState = State::IDLE;

    float shootTime = 0;
};
