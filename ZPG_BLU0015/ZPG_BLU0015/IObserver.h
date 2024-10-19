#pragma once
class IObserver {
public:
    virtual void OnCameraChangedProjection() = 0;
    virtual void OnCameraChangedView() = 0;
};