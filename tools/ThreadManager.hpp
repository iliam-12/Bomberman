/*
** EPITECH PROJECT, 2020
** B-OOP-400-MAR-4-1-arcade-calvin.ruiz
** File description:
** ThreadManager.hpp
*/

#ifndef THREADMANAGER_HPP_
#define THREADMANAGER_HPP_

#include <memory>
#include <thread>
#include <mutex>
#include <vector>

class BaseThreadedModule;

class ThreadManager {
public:
    ThreadManager();
    virtual ~ThreadManager();
    ThreadManager(const ThreadManager &cpy) = delete;
    ThreadManager &operator=(const ThreadManager &src) = delete;

    void startMainloop(int framerate, std::shared_ptr<BaseThreadedModule> module);
    void mainloop();
    // Exit every threads
    void kill() {killAll = true;}
    // Exit mainloop
    void exit() {isAlive = false;}
private:
    static void threadLoop(bool *pIsAlive, bool *pKillAll, int framerate, std::shared_ptr<BaseThreadedModule> module);
    bool isAlive = false;
    bool killAll = false;
    std::mutex mtx;
    std::vector<std::thread> threads;
    std::vector<std::shared_ptr<BaseThreadedModule>> modules;
};

#endif /* THREADMANAGER_HPP_ */
