#ifndef DATACONVERSE_H
#define DATACONVERSE_H

#include <QVariantMap>
#include <QPair>
#include <unordered_map>

#include "json.hpp"

#include <graph.h>

using namespace std;


using json = nlohmann::json;


namespace dataconverse
{


// DEPRECATED
// функция преобразовывает объект типа Graph в QVariantMap
QVariantMap fromGraphToQVariantMap(const Graph& data);

// функция записывает объект в JSON-файл
// создается новый файл
// эта функция выполняется тогда, когда файла с таким именем точно НЕТ
void fromGraphToJSONfile(const Graph& G, const string& graph_name);

// функция преобразовывает JSON-файл в объект типа Graph
// <graph_name>.json - это имя файла, в котором хранится граф
// если эта функция выполняется, то такой файл УЖЕ ТОЧНО ЕСТЬ
Graph fromJSONfileToGraph(const string& graph_name);

};

#endif // DATACONVERSE_H
