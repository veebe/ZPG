#pragma once
/* Vratislav Blunar - BLU0015 */
#include "glm/glm.hpp"
#include "ISubject.h"
#include "IObserver.h"
#include "vector"
#include "LightTypes.h" 

class Light : public ISubject {
public:
    Light(const Light& ACopy);

    glm::vec3 GetLightPosition();
    glm::vec3 GetLightColor();
    float GetLightStrength();
    LightTypes GetLightType();

    void SetLightPostion(glm::vec3 APosition);
    void SetLightColor(glm::vec3 AColor);

protected:
    Light();
    Light(glm::vec3 AColor);
    Light(glm::vec3 AColor, float AStrength);
    Light(glm::vec3 AColor, LightTypes ALightType);
    Light(glm::vec3 AColor, glm::vec3 APosition);
    Light(glm::vec3 AColor, glm::vec3 APosition, LightTypes ALightType);
    Light(glm::vec3 AColor, glm::vec3 APosition, float AStrength, LightTypes ALightType);
    Light(LightTypes ALightType);
    Light(float AStrength);

    void Notify(NotifyType Atype) override;

    glm::vec3 Position = glm::vec3(0.0, 10.0, 0.0); 
    glm::vec3 Color = glm::vec3(1.0, 1.0, 1.0);
    float Strength = 30;
    LightTypes LightType = UNDEFINED;
};
