#pragma once
class Observer {
public:
    virtual void OnCameraChangedProjection() = 0;
    virtual void OnCameraChangedView() = 0;
};