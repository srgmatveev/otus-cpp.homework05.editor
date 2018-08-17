#pragma once
#include <memory>
#include "Shapes.h"
#include <vector>

Interface ImportDocument{
        public:
        virtual  std::vector<std::shared_ptr<IShape>> Import_from_Document() = 0;
        virtual ~ImportDocument() = default;
};


class ImportFromFileSystem:public ImportDocument{
public:
    ImportFromFileSystem(const std::string &file_name):ImportDocument(), _file_name(file_name){}
    std::vector<std::shared_ptr<IShape>> Import_from_Document() override {
        Logger::Instance().info("Import from filesystem file " + _file_name);
        std::vector<std::shared_ptr<IShape>> shapes{};
        std::shared_ptr<IShape> circle = std::make_shared<Circle>(Point{1,8},2);
        shapes.emplace_back(circle);
        return shapes;
    }
    ~ImportFromFileSystem() override = default;

private:
    std::string _file_name{};
};

class ImportFromSQLDatabase:public ImportDocument{
public:
    ImportFromSQLDatabase(const std::string &db_name, const std::string& connect_string):ImportDocument(), _db_name(db_name),
                                                                                         _connect_string(connect_string){
        Logger::Instance().info("Try connect to Database with connect string " + _connect_string );
        Logger::Instance().info("Connect to Database " + _db_name + " successful");
    }
    std::vector<std::shared_ptr<IShape>> Import_from_Document() override {
        Logger::Instance().info("Import from Database " + _db_name);
        std::vector<std::shared_ptr<IShape>> shapes{};
        std::shared_ptr<IShape> circle = std::make_shared<Circle>(Point{1,8},2);
        shapes.emplace_back(circle);
        return shapes;
    }
    ~ImportFromSQLDatabase() override = default;

private:
    std::string _db_name{};
    std::string _connect_string{};
};


Interface IExportDocument{
public:
    virtual  void ExportToDocument(const std::vector<std::shared_ptr<IShape>>&) = 0;
    virtual ~IExportDocument() = default;
    virtual std::string get_doc_name() = 0;
};

class ExportToFile:public IExportDocument{
public:
    ExportToFile(const std::string &file_name):IExportDocument(),  _file_name(file_name){}
    void ExportToDocument(const std::vector<std::shared_ptr<IShape>>& vec) override {
        for(auto&i : vec) {
            Logger::Instance().info("Export shape");
        }
    }
    ~ExportToFile() override = default;

    std::string get_doc_name() {return _file_name;}
private:
    std::string _file_name{};
};


class ExportToSQLDatabase:public IExportDocument{
public:
    ExportToSQLDatabase(const std::string& DB_name,
                        const std::string& connection_name):IExportDocument(),  _DB_name(DB_name),
                                                            _connection_name(connection_name){}
    void ExportToDocument(const std::vector<std::shared_ptr<IShape>>& vec) override {
        for(auto&i : vec) {
            Logger::Instance().info("Export shape");
        }
    }
    ~ExportToSQLDatabase() override = default;

    std::string get_doc_name() {return "SQL Database " + _DB_name;}
private:
    std::string _DB_name{};
    std::string _connection_name{};
};