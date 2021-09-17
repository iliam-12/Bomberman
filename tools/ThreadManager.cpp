/*
** EPITECH PROJECT, 2020
** B-OOP-400-MAR-4-1-arcade-calvin.ruiz
** File description:
** ThreadManager.cpp
*/
#include "ThreadManager.hpp"
#include "BaseThreadedModule.hpp"
#include <chrono>
#include <iostream>

ThreadManager::ThreadManager() {}

ThreadManager::~ThreadManager() {}

void ThreadManager::mainloop()
{
    bool aliveProcess = false;
    int timeout = 600; // 30 seconds

    while (!aliveProcess && timeout--) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        aliveProcess = true;
        for (auto &module : modules) {
            aliveProcess &= module->isReady();
        }
    }
    if (timeout == -1) {
        killAll = true;
        std::cerr << "Timeout : Modules has taken too many time to start.\n";
        return;
    }
    isAlive = true;
    while (isAlive) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        mtx.lock();
        for (unsigned short i = 0; i < modules.size(); ++i) {
            if (!modules[i]->isReady()) {
                threads[i].join();
                modules.erase(modules.begin()+i);
                threads.erase(threads.begin()+i--);
            }
        }
        mtx.unlock();
        if (modules.empty()) {
            if (timeout-- == 0)
                break;
        } else
            timeout = 5; // Let 1/2 second to launch another thread
    }
    isAlive = false;
    for (auto &th : threads) {
        th.join();
    }
    threads.clear();
    modules.clear();
}

void ThreadManager::startMainloop(int framerate, std::shared_ptr<BaseThreadedModule> module)
{
    if (isAlive) {
        mtx.lock();
        modules.push_back(module);
        threads.emplace_back(threadLoop, &isAlive, &killAll, framerate, module);
        mtx.unlock();
    } else {
        modules.push_back(module);
        threads.emplace_back(threadLoop, &isAlive, &killAll, framerate, module);
    }
}

void ThreadManager::threadLoop(bool *pIsAlive, bool *pKillAll, int framerate, std::shared_ptr<BaseThreadedModule> module)
{
    bool &isAlive = *pIsAlive;
    bool &killAll = *pKillAll;
    module->init();

    if (!module->isReady()) {
        std::cerr << "Warning : This module have not been successfully initialized\n";
        return;
    }
    // Wait other threads
    while (!isAlive && !killAll) // isPaused is set to true in case of timeout
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 100 check per second

    auto delay = std::chrono::duration<int, std::ratio<1,1000000>>(1000000 / framerate);
    auto clock = std::chrono::system_clock::now();
    while (isAlive && !killAll && module->isReady()) {
        clock += delay;
        if (module->paused)
            module->onPausePre();
        else
            module->update();
        module->refresh();
        if (module->paused)
            module->onPausePost();
        else
            module->postUpdate();
        std::this_thread::sleep_until(clock);
    }
    module->destroyAsync();
    if (!module->isReady())
        return;
    while (isAlive)
        std::this_thread::sleep_for(std::chrono::milliseconds(10)); // 100 check per second
    module->destroySync();
}
