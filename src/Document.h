#pragma once

#include <string>
#include <memory>
#include <vector>
#include "utils.h"
#include "Shapes.h"
#include "Import_Export.h"

Interface IDocument {
public:
    virtual void init_on_create() = 0;

    virtual void add_object(std::shared_ptr<IShape>&) = 0;

    virtual std::vector<std::shared_ptr<IShape>> get_objects() = 0;

    virtual void delete_selected() = 0;

    virtual std::string get_caption() = 0;

    virtual void import_doc(std::unique_ptr<ImportDocument>) = 0;

    virtual void export_doc(std::unique_ptr<IExportDocument>) = 0;

    virtual ~IDocument() = default;

};


class Document : public IDocument {
public:
    /// Номер документа
    static size_t doc_counter;
    
    Document() = default;

    void init_on_create() {
        _caption = "new_document" + std::to_string(++Document::doc_counter) + ".doc";
        Logger::Instance().info("Create new vector document \"" + _caption + "\"");
    }

    void add_object(std::shared_ptr<IShape>& obj) override {
        objects.emplace_back(obj);
        obj->draw();
    }

    std::vector<std::shared_ptr<IShape>> get_objects() override {
        return objects;
    }

    void delete_selected() {
        if (objects.size()) {
            Logger::Instance().info(objects.at(objects.size() - 1)->string_info(true));
            objects.pop_back();
        }
    }

    std::string get_caption() { return _caption; }

    void import_doc(std::unique_ptr<ImportDocument> imp) override {
        Logger::Instance().info("Begin import to " + _caption + " ...");

        for ( auto &i : imp->Import_from_Document())
            add_object(i);

        Logger::Instance().info("End import to " + _caption + " ...");
    }

    void export_doc(std::unique_ptr<IExportDocument> exp) override {
        Logger::Instance().info("Begin export " + _caption + " to " + exp->get_doc_name() + " ...");
        exp->ExportToDocument(objects);
        Logger::Instance().info("End export " + _caption + " to " + exp->get_doc_name() + " ...");
    }

    virtual ~Document() = default;

private:
    std::string _caption{};
    std::vector<std::shared_ptr<IShape>> objects{};
};

size_t Document::doc_counter = 0;


