#include "lab_m1/tema2/Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "components/transform.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    // CreateTank();
    myTank = new Tank();
    myTank->Init();

    camera = new implemented::CameraT2();
    camera->Set(glm::vec3(myTank->getPosition()) + glm::vec3(0, 4, 8.f), glm::vec3(myTank->getPosition().x , myTank->getPosition().y + 2, myTank->getPosition().z), glm::vec3(0, 1, 0));
    
    projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);

    {
        Mesh* mesh = new Mesh("corp");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "corp.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("turela");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "turela.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("tun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "tun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("senile");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "senile.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("glont");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "glont.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh* mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        vector<VertexFormat> vertices
        {
            VertexFormat(glm::vec3(0, 0,  0), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3( 1, 0,  1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(1,  0,  -1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3( -1,  0,  -1), glm::vec3(0, 0, 1)),
            VertexFormat(glm::vec3(-1, -0, 1), glm::vec3(0, 0, -1)),
        };

        vector<unsigned int> indices =
        {
            1,2,3,
            3,4,1,
        };

        CreateMesh("plan", vertices, indices);
    }

    {
        Shader *shader = new Shader("ShaderT2");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    for (int i = 0; i < 10; i++)
    {
        circle.push_back(make_tuple(40 * cos(i * 36 * M_PI /180) , 40 * sin( i * 36 * M_PI /180)));
        cout << get<0>(circle[i]) << " " << get<1>(circle[i]) << "\n";
    }


    // for (int i = 0; i < 7; i++)
    // {
    //     // putting random buildings on the map
    //     Building *b = new Building();
    //     b->setPositionXYZ(rand() % 100 - 50, 0 , rand() % 100 - 50);
    //     b->setScale(rand() % 20 + 10);
    //     vector<float> cr1 = {b->getPosition().x - b->getScale()/2 , b->getPosition().z - b->getScale()/2};
    //     vector<float> cr2 = {b->getPosition().x + b->getScale()/2 , b->getPosition().z + b->getScale()/2};
    //     vector<float> cr3 = {b->getPosition().x - b->getScale()/2 , b->getPosition().z + b->getScale()/2};
    //     vector<float> cr4 = {b->getPosition().x + b->getScale()/2 , b->getPosition().z - b->getScale()/2};
    //     b->setCorners({cr1 , cr2 , cr3 , cr4});
    //     buildings.push_back(*b);
    // }

    for (int i = 0; i < 7; i++)
    {
        Building *b = new Building();
        int x , y;
        x = rand() % 100 - 50;
        y = rand() % 100 - 50;
        // found x y so that the building is not on the circle

        while(fabs(x) < 40 && fabs(y) < 40)
        {
            x = rand() % 100 - 50;
            y = rand() % 100 - 50;
        }

        
        b->setPositionXYZ(x, 0 , y);
        b->setScale(rand() % 15 + 6);
        vector<float> cr1 = {b->getPosition().x - b->getScale()/2 , b->getPosition().z - b->getScale()/2};
        vector<float> cr2 = {b->getPosition().x + b->getScale()/2 , b->getPosition().z + b->getScale()/2};
        vector<float> cr3 = {b->getPosition().x - b->getScale()/2 , b->getPosition().z + b->getScale()/2};
        vector<float> cr4 = {b->getPosition().x + b->getScale()/2 , b->getPosition().z - b->getScale()/2};
        b->setCorners({cr1 , cr2 , cr3 , cr4});
        buildings.push_back(*b);
        
    }
    

    for (int i = 0; i < 7; i++)
    {
        EnemyTank *e = new EnemyTank();
        e->Init();
        // e->position = glm::vec3(rand() % 200 - 50, 0 , rand() % 200 - 50);
        int x , y;
        x = rand() % 100 - 50;
        y = rand() % 100 - 50;

        while(fabs(x) > 40 && fabs(y) > 40)
        {
            x = rand() % 100 - 50;
            y = rand() % 100 - 50;
        }

        e->position = glm::vec3(x, 0 , y);
        
        enemyTanks.push_back(*e);
        e->color = glm::vec3( 150/255.f, 0, 0);
        e->changeDirectionTime = rand() % 5 + 1;
    }
}

Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Create the VBO and bind it
    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // Create the IBO and bind it
    unsigned int IBO;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

    // Send indices data into the IBO buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // Set vertex position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // Unbind the VAO
    glBindVertexArray(0);

    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
    meshes[name]->vertices = vertices;
    meshes[name]->indices = indices;
    return meshes[name];
}

void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 162/255.f, 232/255.f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    clock += deltaTimeSeconds;
    if (clock - initalclock > 60)
    {
        exit (0);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::scale(modelMatrix, glm::vec3(200.f));
        RenderMesh(meshes["plan"], shaders["ShaderT2"], modelMatrix , glm::vec3(0, 200/255.f, 64/255.f) , 3);
    }
    
    RenderTank();
    MoveProjectile(deltaTimeSeconds);
    RenderBuildings();
    ChangeEnemyTanksDirection(deltaTimeSeconds);
    RenderEnemyTanks(deltaTimeSeconds);
    CheckCollisionTankEnemyTanks(deltaTimeSeconds);
    CheckEnemyTanksShoot(deltaTimeSeconds);
    EnemyTanksShoot( deltaTimeSeconds);
    EnemyTanksShootPlayer(deltaTimeSeconds);

    if (myTank->getHealth() <= 0)
    {
        exit(0);
    }
}


void Tema2::FrameEnd()
{
    // DrawCoordinateSystem(camera->GetViewMatrix() , projectionMatrix);
}


void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix, const glm::vec3 & color , float health)
{ 
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int locationModel = glGetUniformLocation(shader->program , "Model");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(locationModel, 1, GL_FALSE,  glm::value_ptr(modelMatrix));
    
    // TODO(student): Get shader location for uniform mat4 "View"
    int locationView = glGetUniformLocation(shader->program, "View");

    // TODO(student): Set shader uniform "View" to viewMatrix
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(locationView, 1, GL_FALSE , glm::value_ptr(camera->GetViewMatrix()));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int locationProject = glGetUniformLocation(shader->program , "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(locationProject, 1, GL_FALSE , glm::value_ptr(projectionMatrix));

    int loc = glGetUniformLocation(shader->program, "Color");
    glUniform3fv(loc , 1 , glm::value_ptr(color));

    int locHealth = glGetUniformLocation(shader->program, "health");
    glUniform1f(locHealth , health);
    
    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)){
        if (window->KeyHold(GLFW_KEY_A))
        {
            angle += deltaTime * 57;
            myTank->setTankAngle(angle);
            myTank->setForward(glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getForward(), 0)));
            myTank->setForwardTurela( glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getFowardTurela(), 0)));
            camera->TranslateForward(6);
            camera->RotateThirdPerson_OY(deltaTime);
            camera->TranslateForward(-6);
        }
        if (window->KeyHold(GLFW_KEY_D))
        {
            angle -= deltaTime * 57;
            myTank->setTankAngle(angle);
            myTank->setForward(glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(-deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getForward(), 0)));
            myTank->setForwardTurela(glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(-deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getFowardTurela(), 0)));
            camera->TranslateForward(6);
            camera->RotateThirdPerson_OY(-deltaTime);
            camera->TranslateForward(-6);
        }
        if (window->KeyHold(GLFW_KEY_W))
        {
            if (CheckCollisionTankBuildings(deltaTime))
            {
                return;
            }
            glm::vec3 dir = glm::normalize(glm::vec3(myTank->getForward().x , 0 , myTank->getForward().z));
            myTank->setPositionXYZ(myTank->getPosition().x + deltaTime * 5 * dir.x, myTank->getPosition().y , myTank->getPosition().z + deltaTime * 5 * dir.z);
            
            camera->MoveForward(+deltaTime * 5);
        }
        if (window->KeyHold(GLFW_KEY_S))
        {
            if (CheckCollisionTankBuildings(-deltaTime))
            {
                return;
            }
            glm::vec3 dir = glm::normalize(glm::vec3(myTank->getForward().x , 0 , myTank->getForward().z));
            myTank->setPositionXYZ(myTank->getPosition().x - deltaTime * 5 * dir.x, myTank->getPosition().y , myTank->getPosition().z - deltaTime * 5 * dir.z);
            
            camera->MoveForward(-deltaTime * 5);
        }
    }
} 


void Tema2::OnKeyPress(int key, int mods)
{
    
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        camera->TranslateForward(6);
        camera->RotateThirdPerson_OY( -deltaX * 0.002f);
        camera->TranslateForward(-6);
    } else
    {
        myTank->setTurelaAngle(myTank->getTurelaAngle() - deltaX * 0.2f);
        myTank->setForwardTurela(glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(-deltaX * 0.2f), glm::vec3(0, 1, 0)) * glm::vec4(myTank->getFowardTurela(), 0)));
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event

    if ( IS_BIT_SET( button , GLFW_MOUSE_BUTTON_LEFT ) )
    {
        myTank->shoot();
        CheckCollisionProjectileTank(0 , myTank->projectiles[myTank->projectiles.size() - 1]);
    }
    
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
    
}


void Tema2::OnWindowResize(int width, int height)
{
    
}

void Tema2::RenderTank()
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->getPosition()));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(angle) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["senile"], shaders["ShaderT2"], modelMatrix , glm::vec3(50.f/255, 50.f/255, 50.f/255) , myTank->getHealth());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->getPosition()));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(angle) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["corp"], shaders["ShaderT2"], modelMatrix , glm::vec3(15.f/255, 39.f/255, 10.f/255) , myTank->getHealth());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->getPosition()));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(angle) , glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(myTank->getTurelaAngle()) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["turela"], shaders["ShaderT2"], modelMatrix , glm::vec3(30.f/255, 49.f/255, 30.f/255) , myTank->getHealth());
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->getPosition()));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(angle) , glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(myTank->getTurelaAngle()) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["tun"], shaders["ShaderT2"], modelMatrix , glm::vec3(50.f/255, 50.f/255, 50.f/255) , myTank->getHealth());
    }
}

void Tema2::MoveProjectile(float deltaTimeSeconds)
{
    for (int i = 0; i < myTank->projectiles.size(); i++)
    {
        glm::vec3 dir = glm::normalize(glm::vec3(myTank->projectiles[i].getForward().x , 0 , myTank->projectiles[i].getForward().z));
        myTank->projectiles[i].setPositionXYZ( myTank->projectiles[i].getPosition().x + deltaTimeSeconds * 7 * dir.x , myTank->projectiles[i].getPosition().y , myTank->projectiles[i].getPosition().z + deltaTimeSeconds * 7 * dir.z);

        if (myTank->projectiles[i].ttl < 0)
        {
            myTank->projectiles.erase(myTank->projectiles.begin() + i);
            i--;
            continue;
        } else {
            if (CheckCollisionProjectileBuildings(deltaTimeSeconds , &myTank->projectiles[i]))
            {
                myTank->projectiles.erase(myTank->projectiles.begin() + i);
                i--;
                continue;
            }
            if (CheckCollisionProjectileTank(deltaTimeSeconds , myTank->projectiles[i]))
            {
                myTank->projectiles.erase(myTank->projectiles.begin() + i);
                i--;
                continue;
            }
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(myTank->projectiles[i].getPosition()));
            modelMatrix = glm::rotate(modelMatrix , RADIANS(myTank->projectiles[i].getTurelaAngle() + angle) , glm::vec3(0, 1, 0));
            RenderMesh(meshes["glont"], shaders["ShaderT2"], modelMatrix , glm::vec3(1, 0, 0) , 3);
        }
        myTank->projectiles[i].ttl -= deltaTimeSeconds;
    }
}

void Tema2::RenderBuildings()
{
    for (int i = 0; i < buildings.size(); i++)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(buildings[i].getPosition()));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(buildings[i].getScale() , buildings[i].getScale() * 3 , buildings[i].getScale()));
        RenderMesh(meshes["box"], shaders["ShaderT2"], modelMatrix , glm::vec3(100.f/255, 100.f/255, 100.f/255) , 0);

        for (int j = 0; j < buildings[i].getCorners().size(); j++)
        {
            glm::mat4 modelMatrix = glm::mat4(1);
            modelMatrix = glm::translate(modelMatrix, glm::vec3(buildings[i].getCorners()[j][0] , 0 , buildings[i].getCorners()[j][1]));
            RenderMesh(meshes["box"], shaders["ShaderT2"], modelMatrix , glm::vec3(1,1,1) , 0);
        }
    }
}

bool Tema2::CheckCollisionTankBuildings(float deltaTime)
{
    for (int i = 0; i < buildings.size(); i++)
    {
        glm::vec3 dir = glm::normalize(glm::vec3(myTank->getForward().x , 0 , myTank->getForward().z));
        float TankPosX = myTank->getPosition().x - myTank->getRadius() + deltaTime * 5 * dir.x;
        float TankPosY = myTank->getPosition().z - myTank->getRadius() + deltaTime * 5 * dir.z;
        if (TankPosX > buildings[i].getCorners()[0][0] && TankPosX < buildings[i].getCorners()[1][0] && TankPosY > buildings[i].getCorners()[0][1] && TankPosY < buildings[i].getCorners()[1][1])
        {
            return true;
        }
    }
    return false;
}

bool Tema2::CheckCollisionProjectileBuildings(float deltaTime , Projetile *projetile)
{
    for (int i = 0; i < buildings.size(); i++)
    {
        glm::vec3 dir = glm::normalize(glm::vec3(projetile->getForward().x , 0 , projetile->getForward().z));
        float TankPosX = projetile->getPosition().x - projetile->radius + deltaTime * 7 * dir.x;
        float TankPosY = projetile->getPosition().z - projetile->radius + deltaTime * 7 * dir.z;
        if (TankPosX > buildings[i].getCorners()[0][0] && TankPosX < buildings[i].getCorners()[1][0] && TankPosY > buildings[i].getCorners()[0][1] && TankPosY < buildings[i].getCorners()[1][1])
        {
            return true;
        }
    }
    return false;
}

void Tema2::ChangeEnemyTanksDirection(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        if (enemyTanks[i].changeDirectionTime <= 0)
        {
            enemyTanks[i].moveObject.Update();
            enemyTanks[i].changeDirectionTime = rand() % 5 + 1;
            enemyTanks[i].currentState = enemyTanks[i].moveObject.GetState();
            // cout << "Tank " << i << " changed direction.\n";
        } else {
            enemyTanks[i].changeDirectionTime -= deltaTime;
        }
    }
}

void Tema2::RenderEnemyTanks(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        if (enemyTanks[i].health <= 0)
        {
            enemyTanks.erase(enemyTanks.begin() + i);
            i--;
            continue;
        }
        switch (enemyTanks[i].currentState)
        {
            case State::IDLE:
                {
                    MoveEnemyTanks( deltaTime , &enemyTanks[i]);
                    
                    break;
                }

            case State::FORWARD:
                {
                    if (CheckCollisionTankBuildings(deltaTime))
                    {
                        enemyTanks[i].moveObject.Update();
                        enemyTanks[i].currentState = enemyTanks[i].moveObject.GetState();
                        enemyTanks[i].changeDirectionTime = rand() % 5 + 1;
                        break;
                    }
                    
                    glm::vec3 dir = glm::normalize(glm::vec3(enemyTanks[i].forward.x , 0 , enemyTanks[i].forward.z));
                    enemyTanks[i].position = glm::vec3(enemyTanks[i].position.x + deltaTime * 5 * dir.x, enemyTanks[i].position.y , enemyTanks[i].position.z + deltaTime * 5 * dir.z);

                    MoveEnemyTanks(deltaTime , &enemyTanks[i]);
                    
                    break;
                }

            case State::BACKWARD:
                {

                    if (CheckCollisionTankBuildings(-deltaTime))
                    {
                        enemyTanks[i].moveObject.Update();
                        enemyTanks[i].currentState = enemyTanks[i].moveObject.GetState();
                        enemyTanks[i].changeDirectionTime = rand() % 5 + 1;
                        break;
                    }
                    
                    glm::vec3 dir = glm::normalize(glm::vec3(enemyTanks[i].forward.x , 0 , enemyTanks[i].forward.z));
                    enemyTanks[i].position = glm::vec3(enemyTanks[i].position.x - deltaTime * 5 * dir.x, enemyTanks[i].position.y , enemyTanks[i].position.z - deltaTime * 5 * dir.z);

                    MoveEnemyTanks(deltaTime , &enemyTanks[i]);
                    
                    break;
                }

            case State::LEFT:
                {
                    // cout << "left\n";
                    enemyTanks[i].EnemyTank_ang += deltaTime * 57;
                    enemyTanks[i].turela_ang += deltaTime * 57;
                    enemyTanks[i].forward = glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(enemyTanks[i].forward, 0));
                    enemyTanks[i].forward_turela = glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(enemyTanks[i].forward_turela, 0));
                    
                    MoveEnemyTanks(deltaTime , &enemyTanks[i]);
                    
                    break;
                }

            case State::RIGHT:
                {
                    // cout << "right\n";
                    enemyTanks[i].EnemyTank_ang -= deltaTime * 57;
                    enemyTanks[i].turela_ang -= deltaTime * 57;
                    enemyTanks[i].forward = glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(-deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(enemyTanks[i].forward, 0));
                    enemyTanks[i].forward_turela = glm::normalize(glm::rotate(glm::mat4(1.f), RADIANS(-deltaTime * 57), glm::vec3(0, 1, 0)) * glm::vec4(enemyTanks[i].forward_turela, 0));

                    MoveEnemyTanks(deltaTime , &enemyTanks[i]);
                    
                    break;
                }
        }
    }
}

void Tema2::MoveEnemyTanks(float deltaTime , EnemyTank *enemyTank)
{
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyTank->position));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->EnemyTank_ang) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["senile"], shaders["ShaderT2"], modelMatrix , glm::vec3(128.f/255, 128.f/255, 128.f/255) , enemyTank->health);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyTank->position));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->EnemyTank_ang) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["corp"], shaders["ShaderT2"], modelMatrix , glm::vec3(255/255.f , 128/255.f, 0/255.f) , enemyTank->health);

    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyTank->position));
        // modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->EnemyTank_ang) , glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->turela_ang) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["turela"], shaders["ShaderT2"], modelMatrix , glm::vec3(225/255.f , 98/255.f, 0/255.f) , enemyTank->health);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyTank->position));
        // modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->EnemyTank_ang) , glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTank->turela_ang) , glm::vec3(0, 1, 0));
        RenderMesh(meshes["tun"], shaders["ShaderT2"], modelMatrix , glm::vec3(128.f/255, 128.f/255, 128.f/255) , enemyTank->health);
    }
}

bool Tema2::CheckCollisionTankEnemyTanks(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        glm::vec3 myTankPosition = myTank->getPosition();
        glm::vec3 enemyTankPosition = enemyTanks[i].position;
        auto dis = glm::distance(myTankPosition , enemyTankPosition);
        // cout  << dis << "\n";
        if (dis < myTank->getRadius() + enemyTanks[i].radius)
        {
            auto P = myTank->getRadius() + enemyTanks[i].radius - dis;
            auto dir = glm::normalize(myTankPosition - enemyTankPosition);
            myTank->setPositionXYZ(myTankPosition.x + P * dir.x , myTankPosition.y , myTankPosition.z + P * dir.z);
            enemyTanks[i].position = glm::vec3(enemyTankPosition.x - P * dir.x , enemyTankPosition.y , enemyTankPosition.z - P * dir.z);
            return true;
        }
    }
    return false;
}

bool Tema2::CheckCollisionProjectileTank(float deltaTime , Projetile& projectile)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        glm::vec3 enemyTankPosition = enemyTanks[i].position;
        glm::vec3 projectilePosition = projectile.getPosition();
        auto dis = glm::distance(enemyTankPosition , projectilePosition);
        if (dis < enemyTanks[i].radius + projectile.radius)
        {
            enemyTanks[i].health--;
            return true;
        }
    }
    return false;
}

void Tema2::CheckEnemyTanksShoot(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        if (glm::distance(myTank->getPosition(), enemyTanks[i].position) < 30)
        {
            if (enemyTanks[i].shootTime <= 0)
            {
                enemyTanks[i].shootTime = 3;
                enemyTanks[i].shoot();
            } else {
                enemyTanks[i].shootTime -= deltaTime;
            }
        }
    }
}

void Tema2::EnemyTanksShootPlayer(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        auto myTankPosition = myTank->getPosition();
        auto enemyTankPosition = enemyTanks[i].position;

        if (glm::distance(myTankPosition, enemyTankPosition) < 15)
        {
            enemyTanks[i].currentState = State::IDLE;

            auto dir = glm::normalize(myTankPosition - enemyTankPosition);
            
            auto angle = atan2(dir.z, dir.x);
            enemyTanks[i].turela_ang = -angle * 180 / M_PI - 90;
            enemyTanks[i].forward_turela = dir;
            CheckEnemyTanksShoot( deltaTime);
        }
    }
}

void Tema2::EnemyTanksShoot(float deltaTime)
{
    for (int i = 0; i < enemyTanks.size(); i++)
    {
        for (int j = 0; j < enemyTanks[i].projectiles.size(); j++) 
        {
            glm::vec3 dir = glm::normalize(glm::vec3(enemyTanks[i].projectiles[j].getForward().x , 0 , enemyTanks[i].projectiles[j].getForward().z));
            enemyTanks[i].projectiles[j].setPositionXYZ( enemyTanks[i].projectiles[j].getPosition().x + deltaTime * 7 * dir.x , enemyTanks[i].projectiles[j].getPosition().y , enemyTanks[i].projectiles[j].getPosition().z + deltaTime * 7 * dir.z);

            if (enemyTanks[i].projectiles[j].ttl < 0)
            {
                enemyTanks[i].projectiles.erase(enemyTanks[i].projectiles.begin() + j);
                j--;
                continue;
            } else {
                if (CheckCollisionProjectileBuildings(deltaTime , &enemyTanks[i].projectiles[j]))
                {
                    enemyTanks[i].projectiles.erase(enemyTanks[i].projectiles.begin() + j);
                    j--;
                    continue;
                }
                if (CheckEnemyProjectileMyTank(deltaTime , enemyTanks[i].projectiles[j]))
                {
                    enemyTanks[i].projectiles.erase(enemyTanks[i].projectiles.begin() + j);
                    j--;
                    continue;
                }
                enemyTanks[i].projectiles[j].ttl -= deltaTime;
                glm::mat4 modelMatrix = glm::mat4(1);
                modelMatrix = glm::translate(modelMatrix, glm::vec3(enemyTanks[i].projectiles[j].getPosition()));
                modelMatrix = glm::rotate(modelMatrix , RADIANS(enemyTanks[i].projectiles[j].getTurelaAngle()) , glm::vec3(0, 1, 0));
                RenderMesh(meshes["glont"], shaders["ShaderT2"], modelMatrix , glm::vec3(1, 0, 0) , 0);
            }
        }
    }
}

bool Tema2::CheckEnemyProjectileMyTank(float deltaTime, Projetile& projectile)
{
    glm::vec3 myTankPosition = myTank->getPosition();
    glm::vec3 projectilePosition = projectile.getPosition();
    auto dis = glm::distance(myTankPosition , projectilePosition);
    if (dis < myTank->getRadius() + projectile.radius)
    {
        myTank->setHealth(myTank->getHealth() - 1);
        return true;
    }
    return false;
}

bool Tema2::CheckCollisionEnemyTanksBuildings(float deltaTime, EnemyTank& enemyTank)
{
    // for (int i = 0; i < buildings.size(); i++)
    // {
    //     glm::vec3 dir = glm::normalize(glm::vec3(myTank->getForward().x , 0 , myTank->getForward().z));
    //     float TankPosX = myTank->getPosition().x - myTank->getRadius() + deltaTime * 5 * dir.x;
    //     float TankPosY = myTank->getPosition().z - myTank->getRadius() + deltaTime * 5 * dir.z;
    //     if (TankPosX > buildings[i].getCorners()[0][0] && TankPosX < buildings[i].getCorners()[1][0] && TankPosY > buildings[i].getCorners()[0][1] && TankPosY < buildings[i].getCorners()[1][1])
    //     {
    //         return true;
    //     }
    // }
    // return false;

    for (int i = 0; i < buildings.size(); i++){
        glm::vec3 enemyTankPosition = enemyTank.position;
        glm::vec3 dir = glm::normalize(glm::vec3(enemyTank.forward.x , 0 , enemyTank.forward.z));
        float TankPosX = enemyTankPosition.x - enemyTank.radius + deltaTime * 5 * dir.x;
        float TankPosY = enemyTankPosition.z - enemyTank.radius + deltaTime * 5 * dir.z;
        if (TankPosX > buildings[i].getCorners()[0][0] && TankPosX < buildings[i].getCorners()[1][0] && TankPosY > buildings[i].getCorners()[0][1] && TankPosY < buildings[i].getCorners()[1][1])
        {
            return true;
        }
    }
    return false;
}

