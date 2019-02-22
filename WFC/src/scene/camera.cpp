// I couldn't figure out how to do the spherical camera, but here's as far as I got:

#include "camera.h"
#include <la.h>
#include <iostream>

Camera::Camera() : Camera(400, 400) {
    ref = glm::vec4(0.f, 0.f, 0.f, 1.f);
    eye = glm::vec4(0.f, 10.f, 10.f, 1.f);
    forward = glm::vec4(0.f, 0.f, -1.f, 0.f);
    up = glm::vec4(0.f, 1.f, 0.f, 0.f);
    right = glm::vec4(1.f, 0.f, 0.f, 0.f);
    world_up = up;
}

Camera::Camera(unsigned int w, unsigned int h) :
    Camera(w, h, glm::vec4(0.f, 10.f, 10.f, 1.f), glm::vec4(0.f, 0.f, -1.f, 0.f),
           glm::vec4(0.f, 1.f, 0.f, 0.f), glm::vec4(1.f, 0.f, 0.f, 0.f)) {
}

Camera::Camera(unsigned int w, unsigned int h, const glm::vec4 &e, const glm::vec4 &f,
               const glm::vec4 &u,const glm::vec4 &r) :
    fovy(45),
    width(w),
    height(h),
    near_clip(0.1f),
    far_clip(1000),
    eye(e),
    forward(f),
    up(u),
    world_up(u),
    right(r)
{
    RecomputeAttributes();
}

Camera::Camera(const Camera &c):
    fovy(c.fovy),
    width(c.width),
    height(c.height),
    near_clip(c.near_clip),
    far_clip(c.far_clip),
    aspect(c.aspect),
    ref(c.ref),
    eye(c.eye),
    forward(c.forward),
    up(c.up),
    right(c.right),
    world_up(c.world_up),
    V(c.V),
    H(c.H)
{}


void Camera::RecomputeAttributes()
{
    forward = glm::normalize(ref - eye);
    right = glm::vec4(glm::normalize(glm::cross(glm::vec3(forward), glm::vec3(world_up))), 0);
    up = glm::vec4(glm::cross(glm::vec3(right), glm::vec3(forward)), 0);

    float tan_fovy = tan(glm::radians(fovy/2));
    float len = glm::length(ref - eye);
    aspect = width/height;
    V = glm::vec3(up)*len*tan_fovy;
    H = glm::vec3(right)*len*aspect*tan_fovy;
}

glm::mat4 Camera::getViewProj()
{
    return glm::perspective(glm::radians(fovy),
                            width / (float)height, near_clip, far_clip) * glm::lookAt(glm::vec3(eye), glm::vec3(ref), glm::vec3(up));
}

void Camera::RotateAboutUp(float deg)
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(up));
    forward = rotation * forward;
    right = rotation * right;
    RecomputeAttributes();
}
void Camera::RotateAboutRight(float deg)
{
    glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(deg), glm::vec3(right));
    forward = rotation * forward;
    up = rotation * up;
    RecomputeAttributes();
}

void Camera::TranslateAlongForward(float amt)
{
    glm::vec3 translation = glm::vec3(forward) * amt;
    eye += glm::vec4(translation, 0);
}

void Camera::TranslateAlongRight(float amt)
{
    glm::vec3 translation = glm::vec3(right) * amt;
    eye += glm::vec4(translation, 0);
    ref += glm::vec4(translation, 0);
}
void Camera::TranslateAlongUp(float amt)
{
    glm::vec3 translation = glm::vec3(up) * amt;
    eye += glm::vec4(translation, 0);
    ref += glm::vec4(translation, 0);
}

