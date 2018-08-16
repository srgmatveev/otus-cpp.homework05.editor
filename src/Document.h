#pragma once

#include <string>
#include <memory>
#include <vector>
#include "utils.h"
#include "Shapes.h"

Interface IDocument{
public:
    virtual void init_on_create() = 0;
    virtual void add_object(std::shared_ptr<IShape> ) = 0;
    virtual std::vector<std::shared_ptr<IShape>> get_objects() = 0;
    virtual void delete_selected() =0;
    virtual std::string get_caption()=0;
    virtual ~IDocument() = default;
};


class Document:public IDocument{
public:
    /// Номер документа
    static size_t doc_counter;
    /// Номер объекта
    size_t obj_counter{0};
    Document()= default;
    void init_on_create(){
            _caption = "new_document" + std::to_string(++Document::doc_counter)+ ".doc";
            Logger::Instance().info("Create new vector document \"" + _caption + "\"");
    }

    void add_object(std::shared_ptr<IShape> obj) override {
        objects.emplace_back(obj);
        obj->set_id(++obj_counter);
        obj->draw();
    }

    std::vector<std::shared_ptr<IShape>> get_objects() override {
        return objects;
    }

    void delete_selected(){
        if(objects.size())  {
            Logger::Instance().info(objects.at(objects.size()-1)->string_info(true));
            objects.pop_back();}
    }

    std::string get_caption(){return _caption;}

    virtual ~Document() = default;
private:
    std::string _caption{};
    std::vector<std::shared_ptr<IShape>> objects{};
};

size_t Document::doc_counter=0;


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

    std::string get_doc_name() {return _DB_name;}
private:
    std::string _DB_name{};
    std::string _connection_name{};
};