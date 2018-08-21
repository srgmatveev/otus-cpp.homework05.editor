#pragma once
#include <memory>
#include "Document.h"
#include <vector>
#include <string>
#include <iostream>
class Documents{
public:
    static Documents &Instance() {
        static Documents instance;
        return instance;
    }

    void createNewDocument(std::shared_ptr<IDocument> doc){
        doc->init_on_create();
        documents.emplace_back(doc);
        activeDocument = doc;
    }

std::shared_ptr<IDocument> getActiveDocument() const {
    return activeDocument;
}

void setActiveDocument(std::shared_ptr<IDocument>& actDoc_ptr){
    activeDocument = actDoc_ptr;
 }
private:
    /// Конструктор по умолчанию
    Documents() = default;

    /// Конструктор копии запрещен
    Documents(const Documents &root) = delete;

    /// Конструктор перемещения запрещен
    Documents(Documents &&ths) = delete;

    /// Оператор присваивания запрещен
    Documents& operator=(const Documents &) = delete;
    /// Оператор перемещающего присваивания запрещен
    Documents&& operator = (Documents &&) = delete;
    std::shared_ptr<IDocument> activeDocument;
    std::vector<std::shared_ptr<IDocument>> documents{};
};

