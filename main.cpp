#include <iostream>
#include "Document_Controller.h"
#include "Command.h"
#include "Shapes.h"
int main(){
   std::shared_ptr<IDocument> new_doc = std::make_shared<Document>();
   D_C::instance().Dispatcher(std::make_unique<newDocumentCommand>(new_doc));
   D_C::instance().runCommands();

   std::shared_ptr<IShape> circle = std::make_shared<Circle>(Point{1,8},2);
   D_C::instance().Dispatcher(std::make_unique<drawObjectCommand>(new_doc, circle));
   D_C::instance().runCommands();

   std::shared_ptr<IShape> line = std::make_shared<Line>(Point{1,8},Point{2,5});
   D_C::instance().Dispatcher(std::make_unique<drawObjectCommand>(new_doc, line));
   D_C::instance().runCommands();

   D_C::instance().Dispatcher(std::make_unique<deleteSelectedObjectCommand>(new_doc));
   D_C::instance().runCommands();

   std::shared_ptr<IDocument> new_doc1 = std::make_shared<Document>();
   D_C::instance().Dispatcher(std::make_unique<newDocumentCommand>(new_doc1));
   std::unique_ptr<ImportDocument> rule  =  std::make_unique<ImportFromFileSystem>("file.ai");
   D_C::instance().Dispatcher(std::make_unique<importDocumentCommand>(new_doc1, std::move(rule)));
   D_C::instance().runCommands();


   std::unique_ptr<ImportDocument> rule1  =  std::make_unique<ImportFromSQLDatabase>("shapes.mdf", "//MSSQLServer:\"db_user\":\"password\"@shapes.mdf");
   D_C::instance().Dispatcher(std::make_unique<importDocumentCommand>(new_doc1, std::move(rule1)));
   D_C::instance().runCommands();


   std::unique_ptr<IExportDocument> exp_rule = std::make_unique<ExportToFile>("romashka.ai");
   D_C::instance().Dispatcher(std::make_unique<exportDocumentCommand>(new_doc1, std::move(exp_rule)));
   D_C::instance().runCommands();
}