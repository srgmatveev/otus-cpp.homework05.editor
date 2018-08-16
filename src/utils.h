/**
 * @file utils.h
 * @brief Файл с дополнительными функциями.
 */
#pragma once

#include <iostream>
#include <string>

/// Определение интерфейса
#define Interface class

/**
 * @brief Класс синглтон для логирования.
 */
class Logger {
public:
    /// Ссылка на единственный экземпляр класса
    static Logger &Instance() {
        static Logger instance;
        return instance;
    }

    /// функция вывода информации
    void info(const std::string &message) {
        std::cout << "\tinfo: " << message << std::endl;
    }

    /// функция вывода сообщений в поток ошибок, на которые нужно обратить внимание
    void warn(const std::string &message) {
        std::cerr << "warning: " << message << std::endl;
    }

private:
    /// Конструктор по умолчанию
    Logger() = default;

    /// Конструктор копии запрещен
    Logger(const Logger &root) = delete;

    /// Конструктор перемещения запрещен
    Logger(Logger &&ths) = delete;

    /// Оператор присваивания запрещен
    Logger &operator=(const Logger &) = delete;
};

