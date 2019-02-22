// I couldn't figure out how to do the spherical camera, but here's as far as I got:
#pragma once

#include <la.h>

//A perspective projection camera
//Receives its eye position and reference point from the scene XML file
class Camera
{
public:
    Camera();
    Camera(unsigned int w, unsigned int h);
    Camera(unsigned int w, unsigned int h, const glm::vec4 &e, const glm::vec4 &f,
                   const glm::vec4 &u,const glm::vec4 &r);
    Camera(const Camera &c);

    float fovy;
    unsigned int width, height;  // Screen dimensions
    float near_clip;  // Near clip plane distance
    float far_clip;  // Far clip plane distance

    //Computed attributes
    float aspect;

    glm::vec4 ref; // point in world space towards which the camera is pointing
    glm::vec4 eye; // camera position in world space
    glm::vec4 forward; // vector pointing foward in camera space, aka "look"
    glm::vec4 up; // vector pointing up in camera space
    glm::vec4 right; // vector pointing right in camera space

    glm::vec4 world_up;

    // vertical and horizontal component of the plane of the viewing frustum that passes
    // through the camera's reference point. Used in Camera::Raycast.
    glm::vec3 V, H;


    glm::mat4 getViewProj();

    void RecomputeAttributes();

    void RotateAboutUp(float deg);
    void RotateAboutRight(float deg);

    void TranslateAlongForward(float amt);
    void TranslateAlongRight(float amt);
    void TranslateAlongUp(float amt);

    // attrbutes for polar spherical camera
    glm::vec3 phi; // angle by which we rotate about y-axis
    glm::vec3 theta; // angle by which we rotate about x-axis
    glm::vec3 z; // radius of sphere (distance from reference point)

};
