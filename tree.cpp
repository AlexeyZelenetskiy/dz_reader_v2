#include "tree.h"

tree::Node tree::firstElement(const QString &  xml)
{
    Node item;
    int i = xml.indexOf('<');
    int j = xml.indexOf('>');

    QString core = xml.mid(i + 1, j - i - 1);

    if (core.indexOf(' ') == -1)
    {
        item.name = core;
    }
    else
    {
        if (core[core.size() - 1] != '/')
        {
            item.name = core.mid(0, core.indexOf(' '));
            item.attribute = core.mid(core.indexOf(' '), core.size() - core.indexOf(' '));
        }
        else
        {
            item.name = core.mid(0, core.indexOf(' ')) + '/';
            item.attribute = core.mid(core.indexOf(' '), core.size() - core.indexOf(' ') - 1);
        }
    }

    return item;
}

QString tree::crop(QString & xml, Node & item)
{
    if (item.name[item.name.size() - 1] != '/')
    {
        int i = xml.indexOf('<' + item.name + item.attribute + '>');
        int j = xml.indexOf("</" + item.name + '>');

        int intag = QString('<' + item.name + item.attribute + '>').size(); // size of tag

        QString str = xml.mid(i + intag, j - i - intag);
        QString s = str;

        if (j + item.name.size() + 3 != xml.size())
            xml = xml.mid(j + item.name.size() + 3, xml.size() - j - item.name.size() - 3);
        else
            xml = "";

        if (s.indexOf('<' + item.name + ' ') != -1 || s.indexOf('<' + item.name + '>') != -1)
        {
            int k = 0;

            while (s.indexOf('<' + item.name + ' ') != -1 || s.indexOf('<' + item.name + '>') != -1)
            {

                k = xml.indexOf("</" + item.name + '>');
                s = xml.mid(0, k);
                str += "</" + item.name + '>' + s;
                xml = xml.mid(k + item.name.size() + 3, xml.size() - k - item.name.size() - 3);
            }

            return str;
        }
        else
        {

            return str;
        }
    }
    else
    {
        int i = xml.indexOf('<' + item.name.mid(0, item.name.size() - 1) + item.attribute + "/>");
        int intag = QString('<' + item.name.mid(0, item.name.size() - 1) + item.attribute + "/>").size();
        xml = xml.mid(i + intag, xml.size() - i - intag);
        return QString("");
    }
}


void tree::pars(QString xml, Node & node)
{
    while(xml != "")
    {
        shared_ptr<Node> item (new Node(firstElement(xml).name, "", firstElement(xml).attribute));
        QString str = crop(xml, *item);

        if(str != "")
        {
            if(str.indexOf('<') == -1)
               item->data = str;
            else
            {
               item->data += str.mid(0, str.indexOf('<'));
               if(str[str.size() - 1] != '>')
              {
                   item->data += str.mid(str.lastIndexOf('>') + 1, str.size() - str.lastIndexOf('>') - 1);
                   str = str.mid(0, str.lastIndexOf('>') + 1);
               }
               pars(str, *item);
            }
        }

        if(node.son)
        {
            shared_ptr<Node> current = node.son;

            while(current->brother)
              current = current->brother;

            current->brother = item;
        }
        else
        {
            node.son = item;
        }
    }
}

QString tree::body__()
{

    int i = _xml.indexOf("<body>");

    int tS = QString("<body>").size();

    int j = _xml.lastIndexOf("</body>");

    QString item = _xml.mid(i + tS, j - i - tS);

    return item;
}

shared_ptr<tree::Node> tree::getById(QString _name, shared_ptr<Node> _root)
{
    if(_root == shared_ptr<Node>(nullptr))
        _root = this->root;

    if(_root->name == _name)
        return _root;

    if(_root->son)
        if(auto ptr = getById(_name, _root->son))
         return ptr;

    if(_root->brother)
        if(auto ptr = getById(_name, _root->brother))
           return ptr;

    return shared_ptr<Node>(nullptr);
}
