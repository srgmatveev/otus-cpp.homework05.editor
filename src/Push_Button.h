#pragma once
#include <string.h>
#include "Command.h"
#include "utils.h"
#include "Document_Controller.h"

class pushButtonFactory
{
  public:
    static std::shared_ptr<IDocument> createNewDoc()
    {
        std::shared_ptr<IDocument> new_doc = std::make_shared<Document>();
        D_C::instance().Dispatcher(std::make_unique<newDocumentCommand>(new_doc));
        D_C::instance().runCommands();
        return new_doc;
    }
    static void createCircle(
        const Point &p, const size_t &radius,
        const std::shared_ptr<IDocument> &doc = Documents::Instance().getActiveDocument())
    {
        std::shared_ptr<IShape> circle = std::make_shared<Circle>(p, radius);
        D_C::instance().Dispatcher(std::make_unique<drawObjectCommand>(doc, circle));
        D_C::instance().runCommands();
    }
    static void createLine(
        const Point &p1, const Point &p2,
        const std::shared_ptr<IDocument> &doc = Documents::Instance().getActiveDocument())
    {
        std::shared_ptr<IShape> line = std::make_shared<Line>(p1, p2);
        D_C::instance().Dispatcher(std::make_unique<drawObjectCommand>(doc, line));
        D_C::instance().runCommands();
    }

    static void createRectangle(const Point &top,
                                const size_t &height, const size_t &width, const uint16_t &rotate,
                                const std::shared_ptr<IDocument> &doc = Documents::Instance().getActiveDocument())
    {
        std::shared_ptr<IShape> rect = std::make_shared<Rectangle>(top, height, width, rotate);
        D_C::instance().Dispatcher(std::make_unique<drawObjectCommand>(doc, rect));
        D_C::instance().runCommands();
    }
    static void deleteSelectedObject(const std::shared_ptr<IDocument> &doc =
                                         Documents::Instance().getActiveDocument())
    {
        D_C::instance().Dispatcher(std::make_unique<deleteSelectedObjectCommand>(doc));
        D_C::instance().runCommands();
    }

    static void selectImportFromFile(const std::string &f_name,
                                     const std::shared_ptr<IDocument> &doc =
                                         Documents::Instance().getActiveDocument())
    {
        std::unique_ptr<ImportDocument> imp_rule = std::make_unique<ImportFromFileSystem>(f_name);
        D_C::instance().Dispatcher(std::make_unique<importDocumentCommand>(doc, std::move(imp_rule)));
        D_C::instance().runCommands();
    }
    static void selectImportFromSQLDatabase(const std::string &db_name,
                                            const std::string &connect_str,
                                            const std::shared_ptr<IDocument> &doc =
                                                Documents::Instance().getActiveDocument())
    {
        std::unique_ptr<ImportDocument> imp_rule =
            std::make_unique<ImportFromSQLDatabase>(db_name, connect_str);
        D_C::instance().Dispatcher(std::make_unique<importDocumentCommand>(doc, std::move(imp_rule)));
        D_C::instance().runCommands();
    }
    static void selectExportToFile(const std::string &f_name,
                                   const std::shared_ptr<IDocument> &doc =
                                       Documents::Instance().getActiveDocument())
    {
        std::unique_ptr<IExportDocument> exp_rule = std::make_unique<ExportToFile>(f_name);
        D_C::instance().Dispatcher(std::make_unique<exportDocumentCommand>(doc,
                                                                           std::move(exp_rule)));
        D_C::instance().runCommands();
    }
    static void selectExportToSQLDatabase(const std::string &db_name,
                                          const std::string &connect_str,
                                          const std::shared_ptr<IDocument> &doc =
                                              Documents::Instance().getActiveDocument())
    {
        std::unique_ptr<IExportDocument> exp_rule =
            std::make_unique<ExportToSQLDatabase>(db_name, connect_str);
        D_C::instance().Dispatcher(std::make_unique<exportDocumentCommand>(doc, std::move(exp_rule)));
        D_C::instance().runCommands();
    }
};
