#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <fstream>
#include <locale>
#include <QDebug>
#include <QString>
#include <QDebug>
#include <memory>
#include <exception>

using namespace std;

class tree
{
    struct Node {
        QString name;
        QString data;
        QString attribute;
        shared_ptr<Node> son;
        shared_ptr<Node> brother;

        Node() {}

        Node(QString name, QString data, QString attribute, shared_ptr<Node> son = shared_ptr<Node>(nullptr), shared_ptr<Node> brother = shared_ptr<Node>(nullptr))
            : name(name), data(data), son(son), brother(brother), attribute(attribute) {}

        Node(const Node & node)
            : name(node.name), data(node.data), attribute(node.attribute), son(node.son), brother(node.brother) {}
    };

     shared_ptr<Node> root;
public:
    tree() {}
    tree(QString & xml)
    {
        Node current = firstElement(xml);
        QString name = current.name;
        root = shared_ptr<Node>(new Node(name, "", current.attribute));
        _xml = xml;
        QString str = crop(xml, *root);
        QString item = _xml.mid(_xml.lastIndexOf('<') + 2, _xml.size() - _xml.lastIndexOf('<') - 3);
        if(item == name)
           pars(str, *root);
        else
           throw exception("Malformed xml");

    }

    shared_ptr<Node> getById(QString _name, shared_ptr<Node> _root = shared_ptr<Node>(nullptr));
    QString body__();
private:
    QString _xml;
    void pars(QString  xml, Node & node);
    Node firstElement(const QString & xml);
    QString crop(QString & xml, Node & item);
};

#endif // TREE_H
