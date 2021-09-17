/*
** EPITECH PROJECT, 2020
** B-OOP-400-MAR-4-1-arcade-calvin.ruiz
** File description:
** BaseThreadedModule.hpp
*/

#ifndef BASETHREADEDMODULE_HPP_
#define BASETHREADEDMODULE_HPP_

class BaseThreadedModule {
public:
    BaseThreadedModule(const bool &paused);
    virtual ~BaseThreadedModule();
    BaseThreadedModule(const BaseThreadedModule &cpy) = delete;
    BaseThreadedModule &operator=(const BaseThreadedModule &src) = delete;
    virtual void init() {ready = true;}
    virtual void onPausePre() {}
    virtual void onPausePost() {}
    virtual void update() {}
    virtual void postUpdate() {}
    virtual void refresh() {}
    virtual void destroyAsync() {ready = false;}
    virtual void destroySync() {}
    bool isReady() const {return ready;}
    const bool &paused;
protected:
    bool ready = false;
};

#endif /* BASETHREADEDMODULE_HPP_ */
