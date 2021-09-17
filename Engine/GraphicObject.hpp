/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** GraphicObject.hpp
*/

#ifndef GRAPHICOBJECT_HPP_
#define GRAPHICOBJECT_HPP_

#include <string>
#include <memory>
#include <raylib.h>
#include "Data.hpp"

class GraphicMgr;
class Save;

class GraphicObject {
public:
    // grabbed objects are more performants when they are numerous with the same mesh and material pair
    GraphicObject(const GraphicData &data);
    GraphicObject(std::shared_ptr<GraphicMgr> &master, int mesh = 0, int material = 0, bool grabbed = true);
    GraphicObject(const std::string &filename, int mesh = 0, int material = 0, bool grabbed = true);
    virtual ~GraphicObject();
    GraphicObject(const GraphicObject &cpy) = delete;
    GraphicObject &operator=(const GraphicObject &src) = delete;

    void setMesh(int mesh);
    void setMaterial(int material);
    void setPosition(float x, float z, float y = 0);
    void setRotation(float angle); // in radian
    void useTransform(GraphicObject &obj);
    float getRotation() const;
    std::shared_ptr<GraphicMgr> getMgr() const {
        return master;
    }
    // Call once per frame between GraphicMgr::startDraw and GraphicMgr::draw
    void draw();
    // Force update, only usefull if you don't always draw every GraphicObject and you want to change the GraphicObject you draw
    void forceUpdate();
    GraphicData save() const;
    // Detach from globalisation, use it when an object will be dynamically updated for the next draws
    void detach();
    // Attach to globalisation, use it when an object will no longer be updated
    void attach();
private:
    Matrix matrix {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};
    std::shared_ptr<GraphicMgr> master;
    int mesh;
    int material;
    Vector3 pos;
    float angle = 0;
    bool grabbed;
};

#endif /* GRAPHICOBJECT_HPP_ */
