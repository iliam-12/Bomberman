/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** GraphicMgr.hpp
*/

#ifndef GRAPHICMGR_HPP_
#define GRAPHICMGR_HPP_

#include <string>
#include <memory>
#include <map>
#include <vector>
#include <raylib.h>
class Save;
class GraphicObject;

class GraphicMgr {
public:
    virtual ~GraphicMgr();
    GraphicMgr() = delete;
    GraphicMgr(const GraphicMgr &cpy) = delete;
    GraphicMgr &operator=(const GraphicMgr &src) = delete;

    int getMeshCount() const {
        return model.meshCount;
    }
    int getMaterialCount() const {
        return model.materialCount;
    }

    // Initialize frame for draw 3D objects
    // GraphicObject mustn't be altered between this call and draw
    static void startDraw(const Camera &camera);
    // Effectively draw every GraphicObject previously drawn then switch to 2D mode
    static void draw();
    // Submit frame
    static void endDraw();
    static std::shared_ptr<GraphicMgr> &getMgr(const std::string &filename);
    static std::shared_ptr<GraphicMgr> &getMgr(unsigned short id);
    static void unload();
    static void setPath(const std::string &_path) {
        path = _path;
    }
    static void setTexPath(const std::string &_path) {
        texPath = _path;
    }
    static void loadRef(Save &game);
    static void saveRef(Save &game);

    // INTERNAL USE ONLY
    void submit(int mesh, int material, const Matrix &matrix);
    void draw(int mesh, int material, const Matrix &matrix);
    void draw(const Vector3 &pos, const float angle);
    void clear(int mesh, int material);
    unsigned short getID() {return id;}
    void setupAnim(const std::string &basename);
    std::vector<std::shared_ptr<GraphicObject>> getAnim();
private:
    GraphicMgr(const std::string &filename, bool texDep);
    void subdraw();
    Model model;
    bool texDependency;
    Texture2D texture;
    static std::map<std::string, std::shared_ptr<GraphicMgr>> mgrList;
    static std::vector<std::shared_ptr<GraphicMgr>> ultimateLoader;
    static std::string path;
    static std::string texPath;
    std::vector<bool> filled;
    std::vector<std::vector<Matrix>> draws;
    std::vector<std::shared_ptr<GraphicMgr>> animCore;
    std::weak_ptr<GraphicMgr> handle;
    unsigned short id;
};

#endif /* GRAPHICMGR_HPP_ */
