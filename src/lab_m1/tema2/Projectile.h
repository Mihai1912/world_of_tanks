#pragma once

#include "components/simple_scene.h"


class Projetile : public gfxc::SimpleScene
{
public:
    Projetile()
    {
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        turela_ang = 0;
        ttl = 3;
    };

    ~Projetile() { };

    void Init(){
        position = glm::vec3(0,0,0);
        forward = glm::vec3(0, 0, -1);
        turela_ang = 0;
        ttl = 3;
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
    
    float ttl;
    float radius = 0.5f;
private:
    glm::vec3 position;
    glm::vec3 forward;
    float turela_ang;
};