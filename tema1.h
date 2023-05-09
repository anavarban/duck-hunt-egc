#pragma once

#include "components/simple_scene.h"
#include <ft2build.h>
#include FT_FREETYPE_H


namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float initialAngle, reflectionAngle;

        glm::vec3 bodyColor, headColor, beakColor;
        bool hasEscaped, isShot, isActive;
        float elapsedSinceDuck;
        float distFromOrigin;
        float duckSpeed;
        bool wingFlap;
        float wingAngle;
        bool isGoing;
        bool addX, addY;
        int sgnX, sgnY;
        
        float lx, rx, ly, uy;

        float crossX, crossY;
        glm::vec2 res;
        std::vector<glm::vec3> coords;

        int noDucks, noLives, noBullets;

        bool gameOver;

        int ducksShot;

    };
}   // namespace m1
