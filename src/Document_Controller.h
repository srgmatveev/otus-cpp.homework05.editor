#pragma once

#include <memory>
#include <list>
#include <mutex>
#include <vector>
#include "Command.h"
#include "Document.h"

class D_C {
public:
    static D_C &instance() {
        static D_C instance;
        return instance;
    }

    void Dispatcher(std::unique_ptr<ICommand> cmdPtr) {
        if(cmdPtr) commandQueue.emplace_back(std::move(cmdPtr));
    }

    void runCommands() {
        std::mutex mutex;
        mutex.lock();
        for(auto& item : commandQueue) {
            item -> execute();
        }

        commandQueue.clear();

        mutex.unlock();
    }

private:
    /// Конструктор приложения по умолчанию
    D_C() = default;

    D_C(const D_C &) = delete;

    D_C(D_C &&rhs) = delete;

    D_C &operator=(const D_C &) = delete;


    std::list<std::unique_ptr<ICommand>> commandQueue;
};