/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** GraphicObject.cpp
*/
#include "GraphicObject.hpp"
#include "GraphicMgr.hpp"
#include <cmath>

GraphicObject::GraphicObject(const GraphicData &data) :
    GraphicObject(GraphicMgr::getMgr(data.id), data.mesh, data.material, data.grabbed)
{
    angle = data.c;
    // matrix.m0 = data.c;
    // matrix.m2 = data.s;
    // matrix.m8 = -data.s;
    // matrix.m10 = data.c;
    pos.x = data.x;
    pos.y = data.y;
    pos.z = data.z;
}

GraphicObject::GraphicObject(std::shared_ptr<GraphicMgr> &master, int mesh, int material, bool grabbed) :
    master(master), mesh(mesh), material(material), grabbed(grabbed)
{
    forceUpdate();
}

GraphicObject::GraphicObject(const std::string &filename, int mesh, int material, bool grabbed) :
    master(GraphicMgr::getMgr(filename)), mesh(mesh), material(material), grabbed(grabbed)
{
    forceUpdate();
}

GraphicObject::~GraphicObject()
{
    forceUpdate();
}

void GraphicObject::setMesh(int _mesh)
{
    if (grabbed) {
        master->clear(mesh, material);
        mesh = _mesh;
        master->clear(mesh, material);
    } else
        mesh = _mesh;
}

void GraphicObject::setMaterial(int _material)
{
    if (grabbed) {
        master->clear(mesh, material);
        material = _material;
        master->clear(mesh, material);
    } else
        material = _material;
}

void GraphicObject::setPosition(float x, float z, float y)
{
    // forceUpdate();
    // matrix.m12 = x;
    // matrix.m13 = y;
    // matrix.m14 = z;
    pos.x = x;
    pos.y = y;
    pos.z = z;
}

void GraphicObject::setRotation(float _angle)
{
    // forceUpdate();
    // matrix.m0 = cos(angle);
    // matrix.m2 = sin(angle);
    // matrix.m8 = -matrix.m2;
    // matrix.m10 = matrix.m0;
    angle = -_angle * 180. / 3.1415926;
}

void GraphicObject::draw()
{
    // if (grabbed)
    //     master->submit(mesh, material, matrix);
    // else
    //     master->draw(mesh, material, matrix);
    master->draw(pos, angle);
}

void GraphicObject::forceUpdate()
{
    // if (grabbed)
    //     master->clear(mesh, material);
}

GraphicData GraphicObject::save() const
{
    return (GraphicData({mesh, material, pos.x, pos.y, pos.z,
        angle, 0, master->getID(), grabbed}));
}

void GraphicObject::detach()
{
    if (grabbed) {
        master->clear(mesh, material);
        grabbed = false;
    }
}

void GraphicObject::attach()
{
    if (!grabbed) {
        master->clear(mesh, material);
        grabbed = true;
    }
}

float GraphicObject::getRotation() const
{
    return (angle * (-3.1415926 / 180.));
}

void GraphicObject::useTransform(GraphicObject &obj)
{
    pos = obj.pos;
    angle = obj.angle;
}
