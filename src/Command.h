#pragma once

#include "utils.h"
#include "Document.h"
#include "Documents.h"
#include "Shapes.h"
#include "Import_Export.h"

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

class newDocumentCommand : public Command {
public:
    newDocumentCommand(std::shared_ptr<IDocument> d)
            : Command(d) {
    }

    void execute() override {
        Documents::Instance().createNewDocument(document);
    }

    virtual ~newDocumentCommand() = default;
};


class drawObjectCommand : public Command {
public:
    drawObjectCommand(std::shared_ptr<IDocument> d, std::shared_ptr<IShape> obj)
            : Command(d), _obj(obj) {
    }

    void execute() override {
        if (document)
            document->add_object(_obj);
    }

    virtual ~drawObjectCommand() = default;

protected:
    std::shared_ptr<IShape> _obj;
};

class deleteSelectedObjectCommand : public Command {
public:
    deleteSelectedObjectCommand(std::shared_ptr<IDocument> d)
            : Command(d) {
    }

    void execute() override {
        if (document)
            document->delete_selected();
    }

    virtual ~deleteSelectedObjectCommand() = default;

protected:
    std::shared_ptr<IShape> _obj;
};

class importDocumentCommand : public Command {
public:
    importDocumentCommand(std::shared_ptr<IDocument> d, std::unique_ptr<ImportDocument> imp)
            : Command(d), _imp{std::move(imp)} {
    }

    void execute() override {
        if (document)
            document->import_doc(std::move(_imp));
    }

    virtual ~importDocumentCommand() = default;

private:
    std::unique_ptr<ImportDocument> _imp{nullptr};
};

class exportDocumentCommand : public Command {
public:
    exportDocumentCommand(std::shared_ptr<IDocument> d, std::unique_ptr<IExportDocument> exp)
            : Command(d), _exp(std::move(exp)) {
    }

    void execute() override {
        if (document)
            document->export_doc(std::move(_exp));
    }

    virtual ~exportDocumentCommand() = default;

private:
    std::unique_ptr<IExportDocument> _exp{nullptr};
};
