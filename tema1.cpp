#include "D:\facultate\a3\s1\EGC\gfx-framework-master\build\tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"
#include <windows.h>  


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);



    // Initialize tx and ty (the translation steps)
    translateX = rand() % resolution.x;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;

    // Initialize angularStep
    
    headColor = glm::vec3(0.097, 0.3, 0.15);
    bodyColor = glm::vec3(0.5, 0.36, 0.15);
    beakColor = glm::vec3(1, 0.83, 0.47);
    std::vector<VertexFormat> vertices = {
        VertexFormat(glm::vec3(70, 0, 0), bodyColor),
        VertexFormat(glm::vec3(-70, 0 , 0), bodyColor),
        VertexFormat(glm::vec3(0, 300, 0), bodyColor)
    };

    Mesh* body = object2D::CreateTriangleFromVertexList("body", vertices);
    AddMeshToList(body);



    vertices = {
       VertexFormat(glm::vec3(0, 0, 0), bodyColor),
       VertexFormat(glm::vec3(-150, 0, 0), bodyColor),
       VertexFormat(glm::vec3(0, 40 , 0), bodyColor)
    };

    Mesh* leftWing = object2D::CreateTriangleFromVertexList("leftWing", vertices);
    AddMeshToList(leftWing);

    vertices = {
       VertexFormat(glm::vec3(150, 0, 0), bodyColor),
       VertexFormat(glm::vec3(0, 0, 0), bodyColor),
       VertexFormat(glm::vec3(0, 40 , 0), bodyColor)
    };

    Mesh* rightWing = object2D::CreateTriangleFromVertexList("rightWing", vertices);
    AddMeshToList(rightWing);

    Mesh* head = object2D::CreateCircle("head", glm::vec3(0, 0, 0), 90, headColor, true);
    AddMeshToList(head);

    vertices = {
       VertexFormat(glm::vec3(20, 0, 0), beakColor),
       VertexFormat(glm::vec3(0, 0 , 0), beakColor),
       VertexFormat(glm::vec3(10, 40, 0), beakColor)
    };

    Mesh* beak = object2D::CreateTriangleFromVertexList("beak", vertices);
    AddMeshToList(beak);


    ly = 0;
    uy = 350;
    lx = -70;
    rx = 70;
    vertices = {
        VertexFormat(glm::vec3(70, 0, 0), glm::vec3(0)),
        VertexFormat(glm::vec3(-70, 0 , 0), glm::vec3(0)),
        VertexFormat(glm::vec3(-70, 350, 0), glm::vec3(0)),
        VertexFormat(glm::vec3(70, 350, 0), glm::vec3(0))
    };
    Mesh* hitbox = object2D::CreateQuad("hitbox", vertices, false);
    AddMeshToList(hitbox);


    Mesh* crosshairIn = object2D::CreateCircle("crosshairIn", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1), false);
    AddMeshToList(crosshairIn);
    Mesh* crosshairOut = object2D::CreateCircle("crosshairOut", glm::vec3(0, 0, 0), 1, glm::vec3(1, 1, 1), false);
    AddMeshToList(crosshairOut);


    vertices = {
        VertexFormat(glm::vec3(20, 80, 0), glm::vec3(0.49, 0.39, 0.18)),
        VertexFormat(glm::vec3(-20, 80 , 0), glm::vec3(0.49, 0.39, 0.18)),
        VertexFormat(glm::vec3(0,100,0), glm::vec3(0.49, 0.39, 0.18))
    };
    Mesh* bulletTop = object2D::CreateTriangleFromVertexList("bulletTop", vertices);
    AddMeshToList(bulletTop);

    vertices = {
        VertexFormat(glm::vec3(20, 0, 0), glm::vec3(0.49, 0.39, 0.18)),
        VertexFormat(glm::vec3(-20, 0 , 0), glm::vec3(0.49, 0.39, 0.18)),
        VertexFormat(glm::vec3(-20, 80,0), glm::vec3(0.49, 0.39, 0.18)),
        VertexFormat(glm::vec3(20, 80,0), glm::vec3(0.49, 0.39, 0.18))
    };
    Mesh* bulletBtm = object2D::CreateQuad("bulletBtm", vertices, false);
    AddMeshToList(bulletBtm);

    Mesh* life = object2D::CreateHeart("life", glm::vec3(0, 0, 0), 90, glm::vec3(0.85, 0.4, 0.4), true);
    AddMeshToList(life);


    vertices = {
        VertexFormat(glm::vec3(200, 0, 0), glm::vec3(1)),
        VertexFormat(glm::vec3(-200, 0 , 0), glm::vec3(1)),
        VertexFormat(glm::vec3(-200, 20,0), glm::vec3(1)),
        VertexFormat(glm::vec3(200, 20,0), glm::vec3(1))
    };
    Mesh* scoreOut = object2D::CreateQuad("scoreOut", vertices, false);
    AddMeshToList(scoreOut);

    vertices = {
        VertexFormat(glm::vec3(20, 2, 0), glm::vec3(0.5)),
        VertexFormat(glm::vec3(-20, 2 , 0), glm::vec3(0.5)),
        VertexFormat(glm::vec3(-20, 18,0), glm::vec3(0.5)),
        VertexFormat(glm::vec3(20, 18,0), glm::vec3(0.5))
    };
    Mesh* scorePt = object2D::CreateQuad("scorePt", vertices, true);
    AddMeshToList(scorePt);


    Mesh* lose = object2D::CreateHeart("lose", glm::vec3(0, 0, 0), 90, glm::vec3(0.4, 0.4, 0.85), true);
    AddMeshToList(lose);

    Mesh* win = object2D::CreateHeart("win", glm::vec3(0, 0, 0), 90, glm::vec3(1, 0.4, 0.4), true);
    AddMeshToList(win);

    vertices = {
        VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.4, 0.7, 0.6)),
        VertexFormat(glm::vec3(resolution.x, 0 , 0), glm::vec3(0.4, 0.7, 0.6)),
        VertexFormat(glm::vec3(resolution.x, 20, 0), glm::vec3(0.4, 0.7, 0.6)),
        VertexFormat(glm::vec3(0, 20, 0), glm::vec3(0.4, 0.7, 0.6))
    };
    Mesh* grassBase = object2D::CreateQuad("grassBase", vertices, true);
    AddMeshToList(grassBase);

    vertices = {
        VertexFormat(glm::vec3(-20, 0, 0), glm::vec3(0.4, 0.7, 0.6)),
        VertexFormat(glm::vec3(20, 0, 0), glm::vec3(0.4, 0.7, 0.6)),
        VertexFormat(glm::vec3(0, 60, 0), glm::vec3(0.4, 0.7, 0.6))
    };
    Mesh* grassTop = object2D::CreateTriangleFromVertexList("grassTop", vertices);
    AddMeshToList(grassTop);

    vertices = {
        VertexFormat(glm::vec3(-10, 0, 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(0, 5 , 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(10, 0, 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(0, -5, 0), glm::vec3(0.9, 1, 0.9))
    };
    Mesh* starX = object2D::CreateQuad("starX", vertices, true);
    AddMeshToList(starX);

    vertices = {
        VertexFormat(glm::vec3(0, 20, 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(5, 0 , 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(0, -20, 0), glm::vec3(0.9, 1, 0.9)),
        VertexFormat(glm::vec3(-5, 0, 0), glm::vec3(0.9, 1, 0.9))
    };
    Mesh* starY = object2D::CreateQuad("starY", vertices, true);
    AddMeshToList(starY);


    crossX = window->GetCursorPosition().x;
    crossY = window->GetCursorPosition().y;

    hasEscaped = false;
    isShot = false;
    isActive = true;
    elapsedSinceDuck = 0;


    initialAngle = (float)(rand() % 10) / 10 * 3.1415926 / 2 * pow(-1, rand() % 10);
    if (fabs(initialAngle) - 1.57 <= 0.01) {
        initialAngle += 0.2;
    }
    if (fabs(initialAngle) <= 0.01) {
        initialAngle += 0.2;
    }
    reflectionAngle = 0;

    distFromOrigin = 0;

    duckSpeed = 150;

    wingFlap = true;
    wingAngle = 0;

    isGoing = true;

    addX = true;
    addY = true;

    res = window->GetResolution();

    noDucks = 0;
    noLives = 3;
    noBullets = 3;

    gameOver = false;


    ducksShot = 0;
   

}




void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{

    glm::ivec2 resolution = window->GetResolution();


    modelMatrix = glm::mat3(1);
    RenderMesh2D(meshes["grassBase"], shaders["VertexColor"], modelMatrix);
    float grassTX = 0;
    while (grassTX < res.x + 20) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(grassTX, 0);
        RenderMesh2D(meshes["grassTop"], shaders["VertexColor"], modelMatrix);
        grassTX += 20;
    }


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(crossX, crossY);
    modelMatrix *= transform2D::Scale(0.1, 0.1);
    RenderMesh2D(meshes["crosshairIn"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Scale(2, 2);
    modelMatrix *= transform2D::Translate(0, -2);
    RenderMesh2D(meshes["crosshairOut"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(-initialAngle);
    modelMatrix *= transform2D::Scale(0.5, 0.5);

    
    lx = -70;
    rx = 70;
    ly = 0;
    uy = 350;

    coords = { glm::vec3(lx, ly, 1), glm::vec3(lx, uy, 1), glm::vec3(rx, uy, 1), glm::vec3(rx, ly, 1) };
    // 0 - stg jos, 1, stg sus, 2 drp sus, 3 drp jos ok  
    
    for (int i = 0; i < 4; i++) {
        coords[i] = transform2D::Translate(translateX, translateY) * transform2D::Rotate(-initialAngle) * transform2D::Scale(0.5, 0.5) * coords[i];
    }
   


    modelMatrix *= transform2D::Translate(0, 150);
    RenderMesh2D(meshes["head"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Translate(0, -150);

    RenderMesh2D(meshes["body"], shaders["VertexColor"], modelMatrix);



    modelMatrix *= transform2D::Translate(20, 150);
    modelMatrix *= transform2D::Rotate(-wingAngle);
    RenderMesh2D(meshes["rightWing"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Rotate(wingAngle);
    modelMatrix *= transform2D::Translate(-20, -150);



    modelMatrix *= transform2D::Translate(-20, 150);
    modelMatrix *= transform2D::Rotate(wingAngle);
    RenderMesh2D(meshes["leftWing"], shaders["VertexColor"], modelMatrix);
    modelMatrix *= transform2D::Rotate(-wingAngle);
    modelMatrix *= transform2D::Translate(20, -150);



    if (wingFlap) {
        wingAngle += deltaTimeSeconds * duckSpeed / 30;
        if (wingAngle > 0.5) {
            wingFlap = false;
        }
    }
    else {
        wingAngle -= deltaTimeSeconds * duckSpeed / 30;
        if (wingAngle < -0.5) {
            wingFlap = true;
        }
    }


    RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrix);


    modelMatrix *= transform2D::Translate(0, 350);
    RenderMesh2D(meshes["beak"], shaders["VertexColor"], modelMatrix);


    elapsedSinceDuck += deltaTimeSeconds;
    if (elapsedSinceDuck > 8) {
        hasEscaped = true;
        isActive = false;
        isShot = false;
    }
    if (noBullets == 0) {
        isActive = false;
        hasEscaped = true;
        isShot = false;
    }
    if (hasEscaped) {

        initialAngle = 0;
        translateY += deltaTimeSeconds * 2 * duckSpeed;


        if (translateY > resolution.y) {
            noLives--;
            if (noLives == 0) {
                gameOver = true;
            }
            hasEscaped = false;
            isActive = true; 
            isShot = false;
            translateX = rand() % resolution.x;
            translateY = 0;
            initialAngle = (float)(rand() % 10) / 10 * 3.1415926 / 2 * pow(-1, rand() % 10);
            if (fabs(initialAngle) - 1.57 <= 0.01) {
                initialAngle += 0.2;
            }
            if (fabs(initialAngle) <= 0.01) {
                initialAngle += 0.2;
            }
            elapsedSinceDuck = 0;
            noDucks++;
            if (noDucks % 5 == 0) {
                duckSpeed *= 1.75;
                if (duckSpeed > 600) {
                    duckSpeed = 600;
                }
            }
            noBullets = 3;
        }
        
        
    }
    if (isShot) {

        initialAngle = 3.1415926;
        translateY -= deltaTimeSeconds * 2 * duckSpeed;


        if (translateY < 0) {
            hasEscaped = false;
            isActive = true;
            isShot = false;
            translateX = rand() % resolution.x;
            translateY = 0;
            initialAngle = (float)(rand() % 10) / 10 * 3.1415926 / 2 * pow(-1, rand() % 10);
            if (fabs(initialAngle) - 1.57 <= 0.01) {
                initialAngle += 0.2;
            }
            if (fabs(initialAngle) <= 0.01) {
                initialAngle += 0.2;
            }
            elapsedSinceDuck = 0;
            noDucks++;
            if (noDucks % 5 == 0) {
                duckSpeed *= 1.75;
                if (duckSpeed > 600) {
                    duckSpeed = 600;
                }
            }
            noBullets = 3;
        }


    }
    if (isActive) {
        isGoing = true;

        

        
        translateX += deltaTimeSeconds * duckSpeed * sin(initialAngle);
        translateY += deltaTimeSeconds * duckSpeed * cos(initialAngle);




        if (translateX >= resolution.x) {
            //reflectionAngle = 3.1415926 + initialAngle;
            reflectionAngle = -initialAngle;
            initialAngle = reflectionAngle;
            if (isGoing) {
                modelMatrix *= transform2D::Translate(-translateX, -translateY);
                modelMatrix *= transform2D::Rotate(reflectionAngle);
                modelMatrix *= transform2D::Translate(translateX, translateY);
                isGoing = false;
            }
            
        }
        if (translateY >= resolution.y) {
            reflectionAngle = 3.1415926 - initialAngle;
            initialAngle = reflectionAngle;
            if (isGoing) {
                modelMatrix *= transform2D::Translate(-translateX, -translateY);
                modelMatrix *= transform2D::Rotate(reflectionAngle);
                modelMatrix *= transform2D::Translate(translateX, translateY);
                isGoing = false;
            }
        }
        if (translateX < 0) {
            reflectionAngle = -initialAngle;
            initialAngle = reflectionAngle; 
            if (isGoing) {
                modelMatrix *= transform2D::Translate(-translateX, -translateY);
                modelMatrix *= transform2D::Rotate(reflectionAngle);
                modelMatrix *= transform2D::Translate(translateX, translateY);
                isGoing = false;
            }
        }
        if (translateY < 0) {
            reflectionAngle = 3.1415926 - initialAngle;
            initialAngle = reflectionAngle;
            if (isGoing) {
                modelMatrix *= transform2D::Translate(-translateX, -translateY);
                modelMatrix *= transform2D::Rotate(reflectionAngle);
                modelMatrix *= transform2D::Translate(translateX, translateY);
                isGoing = false;
            }
        }
    }

        
    float statX = 60;

    for (int i = 0; i < noBullets; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(statX, 550);
        modelMatrix *= transform2D::Scale(0.8, 0.8);
        if (!gameOver) {
            RenderMesh2D(meshes["bulletTop"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["bulletBtm"], shaders["VertexColor"], modelMatrix);
        }
        statX += 40;

    }

    

    if (!gameOver) {

        statX = 60;

        for (int i = 0; i < noLives; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(statX, 670);
            modelMatrix *= transform2D::Scale(0.3, 0.3);
            RenderMesh2D(meshes["life"], shaders["VertexColor"], modelMatrix);
            statX += 40;
        }

        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(res.x - 300, res.y - 30);
        RenderMesh2D(meshes["scoreOut"], shaders["VertexColor"], modelMatrix);


        float scoreX = res.x - 480;
        float scoreY = res.y - 30;
        for (int i = 0; i < ducksShot; i++) {
            modelMatrix = glm::mat3(1);
            modelMatrix *= transform2D::Translate(scoreX, scoreY);
            RenderMesh2D(meshes["scorePt"], shaders["VertexColor"], modelMatrix);
            scoreX += 20;
        }


    }

    
    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(652, 169);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(600, 654);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(300, 300);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(890, 180);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1000, 200);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);


    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(400, 400);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(999, 555);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(20, 555);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1200, 700);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(200, 100);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(279, 400);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(1100, 60);
    modelMatrix *= transform2D::Scale(1.4, 1.4);
    RenderMesh2D(meshes["starX"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["starY"], shaders["VertexColor"], modelMatrix);

    if (gameOver) {
        translateX = 50000;
        translateY = 50000;
        
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(res.x / 2, res.y / 2);

        if (noLives == 0) {
            modelMatrix *= transform2D::Rotate(3.1415926);
            RenderMesh2D(meshes["lose"], shaders["VertexColor"], modelMatrix);
        }

        if (ducksShot == 20) {
            RenderMesh2D(meshes["win"], shaders["VertexColor"], modelMatrix);
        }
        
    }


}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    crossX += deltaX;
    crossY += -deltaY;
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    
    
    float pozx, pozy; 
    pozx = mouseX;
    pozy = res.y - mouseY;

    float x1, x2, x3, x4, y1, y2, y3, y4;
    x1 = (pozx - coords[0].x) / (coords[1].x - coords[0].x);
    x2 = (pozx - coords[3].x) / (coords[2].x - coords[3].x);
    x3 = (pozx - coords[1].x) / (coords[2].x - coords[1].x);
    x4 = (pozx - coords[0].x) / (coords[3].x - coords[0].x);
    y1 = (pozy - coords[0].y) / (coords[1].y - coords[0].y);
    y2 = (pozy - coords[3].y) / (coords[2].y - coords[3].y);
    y3 = (pozy - coords[1].y) / (coords[2].y - coords[1].y);
    y4 = (pozy - coords[0].y) / (coords[3].y - coords[0].y);

    float m1, m2, m3, m4;

    m1 = (coords[1].y - coords[0].y) / (coords[1].x - coords[0].x);
    m2 = (coords[2].y - coords[3].y) / (coords[2].x - coords[3].x);
    m3 = (coords[2].y - coords[1].y) / (coords[2].x - coords[1].x);
    m4 = (coords[3].y - coords[0].y) / (coords[3].x - coords[0].x);


    if (m1 > 0)
    {
        m1 = 1;
    } else {
        m1 = -1;
    }

    if (m2 > 0)
    {
        m2 = 1;
    } else {
        m2 = -1;
    }

    if (m3 > 0)
    {
        m3 = 1;
    } else {
        m3 = -1;
    }

    if (m4 > 0)
    {
        m4 = 1;
    } else {
        m4 = -1;
    }

    noBullets--;

    if (
        m1*x1 > m1*y1 &&
        m2*x2 < m2*y2 &&
        m3*x3 > m3*y3 &&
        m4*x4 < m4*y4 
        ) {
        isShot = true;
        ducksShot++;
        if (ducksShot == 20) {
            gameOver = true;
        }
        
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}
