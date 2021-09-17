/*
** EPITECH PROJECT, 2020
** B-YEP-400-MAR-4-1-indiestudio-iliam.amara
** File description:
** GraphicMgr.cpp
*/
#include "GraphicMgr.hpp"
#include "GraphicObject.hpp"
#include "Save.hpp"
#include <cstring>

std::map<std::string, std::shared_ptr<GraphicMgr>> GraphicMgr::mgrList;
std::string GraphicMgr::path = "resources/model/";
std::string GraphicMgr::texPath = "resources/texture/";
std::vector<std::shared_ptr<GraphicMgr>> GraphicMgr::ultimateLoader;

GraphicMgr::GraphicMgr(const std::string &filename, bool texDep) : texDependency(texDep)
{
    if (texDep) {
        model = LoadModelFromMesh(GenMeshPlane(1.6, 1.6, 1, 1));
        texture = LoadTexture(filename.c_str());
        model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    } else {
        model = LoadModel(filename.c_str());
    }
    draws.resize(model.meshCount);
    filled.resize(draws.size());
}

GraphicMgr::~GraphicMgr()
{
    UnloadModel(model);
    if (texDependency)
        UnloadTexture(texture);
}

void GraphicMgr::startDraw(const Camera &camera)
{
    BeginDrawing();
    BeginMode3D(camera);
}

void GraphicMgr::draw()
{
    // for (auto &p : mgrList) {
    //     if (p.second)
    //         p.second->subdraw();
    // }
    EndMode3D();
}

void GraphicMgr::endDraw()
{
    EndDrawing();
}

std::shared_ptr<GraphicMgr> &GraphicMgr::getMgr(const std::string &filename)
{
    std::shared_ptr<GraphicMgr> &mgr = mgrList[filename];

    if (!mgr) {
        if (filename.compare(filename.size() - 4, 4, ".png", 4)) {
            if (filename[0] == '#') {
                mgr = std::shared_ptr<GraphicMgr>(new GraphicMgr(path + filename.substr(1) + ".obj", false));
                mgr->handle = mgr;
                mgr->setupAnim(filename.substr(1));
            } else {
                mgr = std::shared_ptr<GraphicMgr>(new GraphicMgr(path + filename, false));
            }
        } else {
            mgr = std::shared_ptr<GraphicMgr>(new GraphicMgr(texPath + filename, true));
        }
    }
    return mgr;
}

std::shared_ptr<GraphicMgr> &GraphicMgr::getMgr(unsigned short id)
{
    return (ultimateLoader[id]);
}

void GraphicMgr::unload()
{
    mgrList.clear();
}

void GraphicMgr::submit(int mesh, int, const Matrix &matrix)
{
    if (!filled[mesh]) {
        draws[mesh].push_back(matrix);
    }
}

void GraphicMgr::clear(int mesh, int)
{
    if (filled[mesh]) {
        filled[mesh] = false;
        draws[mesh].clear();
    }
}

void GraphicMgr::subdraw()
{
    for (int i = 0; i < (int) draws.size(); ++i) {
        switch (draws[i].size()) {
            case 0:
                break;
            case 1:
                filled[i] = true;
                DrawMesh(model.meshes[i], *model.materials, draws[i].front());
                break;
            default:
                filled[i] = true;
                DrawMeshInstanced(model.meshes[i], *model.materials, draws[i].data(), draws[i].size());
                break;
        }
    }
}

void GraphicMgr::draw(int mesh, int material, const Matrix &matrix)
{
    DrawMesh(model.meshes[mesh], model.materials[material], matrix);
}

void GraphicMgr::draw(const Vector3 &pos, const float angle)
{
    DrawModelEx(model, pos, {0, 1, 0}, angle, {0.5, 0.5, 0.5}, WHITE);
}

void GraphicMgr::loadRef(Save &game)
{
    auto &tmp = game["MgrRefs"];

    ultimateLoader.clear();
    for (unsigned int i = 0; i < tmp.size(); i += 256)
        ultimateLoader.push_back(getMgr(tmp.data() + i));
}

void GraphicMgr::saveRef(Save &game)
{
    int idea = 0;

    auto &tmp = game["MgrRefs"];
    for (auto &pair : mgrList) {
        pair.second->id = idea;
        tmp.resize(++idea * 256);
        memcpy(tmp.data() + ((idea - 1) * 256), pair.first.c_str(), pair.first.size() + 1);
    }
}

void GraphicMgr::setupAnim(const std::string &basename)
{
    animCore.push_back(getMgr(basename + "1l.obj"));
    animCore.push_back(getMgr(basename + "2l.obj"));
    animCore.push_back(getMgr(basename + "1r.obj"));
    animCore.push_back(getMgr(basename + "2r.obj"));
}

std::vector<std::shared_ptr<GraphicObject>> GraphicMgr::getAnim()
{
    if (animCore.empty())
        return (std::vector<std::shared_ptr<GraphicObject>> {});
    auto tmp = handle.lock();
    auto tmp4 = std::make_shared<GraphicObject>(tmp);
    auto tmp0 = std::make_shared<GraphicObject>(animCore[0]);
    auto tmp1 = std::make_shared<GraphicObject>(animCore[1]);
    auto tmp2 = std::make_shared<GraphicObject>(animCore[2]);
    auto tmp3 = std::make_shared<GraphicObject>(animCore[3]);

    std::vector<std::shared_ptr<GraphicObject>> ret =
        {tmp4, tmp0, tmp1, tmp0, tmp4, tmp2, tmp3, tmp2};
    return ret;
}
