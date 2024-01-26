#pragma once

#include "components/simple_scene.h"
#include "Projectile.h"


class Tank : public gfxc::SimpleScene
{
public:
    Tank()
    {
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        forward_turela = glm::vec3(0, 0, -1);
        turela_ang = 0;
    };
    
    ~Tank() { };

    void Init(){
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        forward_turela = glm::vec3(0, 0, -1);
        turela_ang = 0;
    }

    glm::vec3 getPosition()
    {
        return position;
    }

    glm::vec3 getForward(){
        return forward;
    }

    float getTurelaAngle(){
        return turela_ang;
    }

    glm::vec3 getFowardTurela(){
        return forward_turela;
    }

    float getTankAngle(){
        return tank_ang;
    }

    float getRadius(){
        return radius;
    }

    float getHealth(){
        return health;
    }

    void setPositionXYZ(float x , float y , float z)
    {
        position = glm::vec3(x,y,z);
    }

    void setPosition(glm::vec3 pos)
    {
        position = pos;
    }
    
    void setForward(glm::vec3 forward){
        this->forward = forward;
    }

    void setTurelaAngle(float angle){
        turela_ang = angle;
    }

    void setForwardTurela(glm::vec3 forward){
        forward_turela = forward;
    }

    void setTankAngle(float angle){
        tank_ang = angle;
    }

    void setRadius(float radius){
        this->radius = radius;
    }

    void setHealth(float health){
        this->health = health;
    }

    void shoot(){
        Projetile *p = new Projetile();
        p->setPosition(position);
        p->setForward(forward_turela);
        p->setTurelaAngle(turela_ang);
        projectiles.push_back(*p);
    }

    
    std::vector<Projetile> projectiles;
    
private:
    
    glm::vec3 position;
    float health = 3;
    glm::vec3 forward;
    glm::vec3 forward_turela;
    float turela_ang;
    float tank_ang;
    float radius = 1.5f;
};
