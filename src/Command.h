#pragma once

#include "utils.h"
#include "Document.h"
#include "Documents.h"
#include "Shapes.h"

Interface ICommand {
public:
    virtual void execute() = 0;
    virtual ~ICommand() = default;
};

class Command : public ICommand {
public:
    virtual ~Command() = default;
protected:
    Command(std::shared_ptr<IDocument> d)
            : document(d) {}
    std::shared_ptr<IDocument> document;
};

class newDocumentCommand: public Command {
public:
    newDocumentCommand(std::shared_ptr<IDocument> d)
    : Command(d) {
    }

    void execute() override {
      Documents::Instance().createNewDocument(document);
    }

    virtual ~newDocumentCommand() = default;
};


class drawObjectCommand: public Command {
public:
    drawObjectCommand(std::shared_ptr<IDocument> d, std::shared_ptr<IShape> obj)
            : Command(d),_obj(obj)  {
    }

    void execute() override {
      if(document)
        document->add_object(_obj);
    }

    virtual ~drawObjectCommand() = default;
protected:
    std::shared_ptr<IShape> _obj;
};

class deleteSelectedObjectCommand: public Command {
public:
    deleteSelectedObjectCommand(std::shared_ptr<IDocument> d)
            : Command(d)  {
    }

    void execute() override {
        if(document)
            document->delete_selected();
    }

    virtual ~deleteSelectedObjectCommand() = default;
protected:
    std::shared_ptr<IShape> _obj;
};


class importDocumentCommand: public Command {
public:
    importDocumentCommand(std::shared_ptr<IDocument> d, std::unique_ptr<ImportDocument> rule)
            : Command(d), _rule(std::move(rule))  {
    }

    void execute() override {
        if(document) {
            Logger::Instance().info("Begin import from " + document->get_caption());
       for(auto&i : _rule ->Import_from_Document())
                document->add_object(i);
        }
        Logger::Instance().info("End import from " +  document->get_caption());
     }
    virtual ~importDocumentCommand() = default;
protected:
std::unique_ptr<ImportDocument> _rule;
std::shared_ptr<IShape> objects;
};


class exportDocumentCommand: public Command {
public:
    exportDocumentCommand(std::shared_ptr<IDocument> d, std::unique_ptr<IExportDocument> rule)
            : Command(d), _rule(std::move(rule))  {
    }

    void execute() override {
        if(document) {
            Logger::Instance().info("Begin export to " + _rule->get_doc_name());
            _rule->ExportToDocument(document->get_objects());
            Logger::Instance().info("End export to " + _rule->get_doc_name());
        }
    }
    virtual ~exportDocumentCommand() = default;
protected:
    std::unique_ptr<IExportDocument> _rule;
    std::shared_ptr<IShape> objects;
};
