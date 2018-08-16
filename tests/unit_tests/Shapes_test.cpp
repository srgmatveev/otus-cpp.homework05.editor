#include <gmock/gmock.h>
#include "Shapes.h"
#include <string>
using namespace testing;

TEST(IShape_Test, IShape_Test_Correct_Shapes_Test){

    IShape *circle = new Circle(Point{1,2}, 8);
    std::string str = circle->string_info(false);
    ASSERT_EQ(str.substr(0,11),"Draw circle");
    if(circle) delete circle;

    IShape *rect = new Rectangle(Point{5,6}, 8, 9,0);
    str = rect->string_info(false);
    ASSERT_EQ(str.substr(0,14),"Draw rectangle");
    if(rect) delete(rect);

    IShape *line = new Line(Point{5,6}, Point{8, 9});
    str = line->string_info(false);
    ASSERT_EQ(str.substr(0,9),"Draw line");
    if(line) delete(line);

}