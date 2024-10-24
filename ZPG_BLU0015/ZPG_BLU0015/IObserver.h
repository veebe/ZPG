#pragma once
class IObserver {
public:
    virtual void OnCameraChangedProjection() = 0;
    virtual void OnCameraChangedView() = 0;

    virtual void OnLightChangePosition() = 0;
    virtual void OnLightChangeColor() = 0;
};