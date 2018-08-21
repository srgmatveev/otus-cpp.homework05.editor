/**
 * @file Shapes.h
 * @brief Файл описания графических объектов
 */
#pragma once

#include <memory>
#include <sstream>
#include "utils.h"

/**
 * @brief Интерфейс графических объектов
 *
 * Аюстрактный класс IShape
 */
Interface IShape {
public:
    /// Чисто виртуалный метод рисования графических объектов
    virtual void draw() = 0;
    /// Чисто виртуальный метод вывода информации о графическом объекте
    virtual std::string string_info(bool) = 0;
    /// Виртуальный деструктор
    virtual ~IShape(){};
   };

/**
 * @brief Структура для хранения 2D координат точки
 */
struct Point {
    /// Положение на оси абцисс
    int _x{0};
    /// Положение на оси ординат
    int _y{0};
    /// Конструктор, задающий координаты точки
    Point(int x, int y) : _x(x), _y(y) {};
    /// Конструктор по умолчанию, задает нулевые координаты точки
    Point() : _x(0), _y(0) {};
};

/**
 * @brief Класс, рисующий линию 2D
 */
class Line : public IShape {
public:
    /// Конструктор, задающий координаты линии
    Line(const Point &begin, const Point &end) : _begin(begin), _end(end) {}
    /// Реализация метода для отображения линии на Canvas
    void draw() override {
        Logger::Instance().info(string_info());
    }
    /// Виртуальный деструктор
    virtual ~Line(){}
    /// Метод, выводящий информацию о линии
    std::string string_info(bool del_flag = false) override {
        std::ostringstream stream;
        if (del_flag) stream << "Delete ";
        else stream << "Draw ";
        stream << "line from x = " << _begin._x << " y = " << _begin._y;
        stream << " to x = " << _end._x << " y = " << _end._y;
        return stream.str();
    }
private:
    /// Структура, задающая начало линии
    Point _begin;
    /// Структура, задающая конец линии
    Point _end;
};
/**
 * @brief  Класс, рисующий прямоугольник 2D
 */
class Rectangle : public IShape {
public:
    /// Конструктор, задающий координаты вершины, длину, ширину и угол поворота прямоугольника
    Rectangle(const Point &top, const size_t &height, const size_t &width, const uint16_t &rotate = 0) :
            _top(top), _height(height), _width(width), _angle(rotate) {}
    /// Реализация метода для отображения прямоугольника на Canvas
    void draw() override {
        Logger::Instance().info(string_info());
    }
    /// Виртуальный деструктор
    virtual ~Rectangle() {}
    /// Метод, выводящий информацию о прямоугольнике
    std::string string_info(bool del_flag = false) override {
        std::ostringstream stream;
        if (del_flag) stream << "Delete ";
        else stream << "Draw ";
        stream << "rectangle from top {" << _top._x << ", " << _top._y << "} ";
        stream << " with height = " << _height << " width = " << _width;
        stream << " and rotate angle = " << _angle;
        return stream.str();
    }
private:
    /// Структура, задающая вершину прямоугольника
    Point _top{0, 0};
    ///  Высота прямоугольника
    size_t _height{0};
    /// Ширина прямоугольника
    size_t _width{0};
    /// Угол поворота прямоугольника
    uint16_t _angle{0};  
};
/**
 * @brief  Класс, рисующий окружность 2D
 */
class Circle : public IShape {
public:
    /// Конструктор, задающий координаты центра и радиус окружности
    Circle(const Point &center, const size_t &radius) : _center(center), _radius(radius) {}
    /// Реализация метода для отображения окружности на Canvas
    void draw() override {
        Logger::Instance().info(string_info());
    }
    /// Виртуальный деструктор
    virtual ~Circle() {}
    /// Метод, выводящий информацию об окружности
    std::string string_info(bool del_flag = false) override {
        std::ostringstream stream;
        if (del_flag) stream << "Delete ";
        else stream << "Draw ";
        stream << "circle with center at  x = " << _center._x << " y = " << _center._y;
        stream << " with radius = " << _radius;
        return stream.str();
    }
private:
    /// Структура, задающая центр окружности
    Point _center;
    /// Радиус окружности
    size_t _radius;
};
