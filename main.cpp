#include <iostream>
#include "Document_Controller.h"
#include "Command.h"
#include "Shapes.h"
#include "Push_Button.h"
int main()
{
    pushButtonFactory::createNewDoc();
    pushButtonFactory::createCircle(Point{1, 8}, 2);
    pushButtonFactory::createLine(Point{1, 8}, Point{2, 5});
    pushButtonFactory::deleteSelectedObject();
    pushButtonFactory::createNewDoc();
    pushButtonFactory::selectImportFromFile("file.ai");
    pushButtonFactory::selectImportFromSQLDatabase("shapes.mdf",
                                                   "//MSSQLServer:\"db_user\":\"password\"@shapes.mdf");

    pushButtonFactory::selectExportToFile("picture.ai");
    pushButtonFactory::selectExportToSQLDatabase("export_shapes.mdf",
                                                 "//MSSQLServer:\"db_user\":\"password\"@exp_shapes.mdf");
    
}