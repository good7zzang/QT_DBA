#include "m_table_item.h"

M_table_item::M_table_item(QString machine_name,QObject *parent) : QObject(parent)
{
    this->parent = parent;
    La_machine_name = new QLabel("");
    La_machine_name->setText(machine_name);
    La_statue = new QLabel("");
    La_object_count = new QLabel("");
    La_current_count = new QLabel("");
}
