#include "QuadTree.h"
#include <iostream>
#include <fstream>
#include <cmath>

// -------------------------------------------------------------- NODOS DEL QUAD TREE --------------------------------------------------------------

QuadTreeNode::QuadTreeNode(int x, int y, int w, int h, int max_p)
    : pos(x, y), width(w), height(h), max_points(max_p), divided(false) {

    for (int i = 0; i < 4; ++i) 
        children[i] = nullptr;
}

bool QuadTreeNode::insert(Point p) {

    if (p.x < pos.x - width / 2 || p.x > pos.x + width / 2 ||
        p.y < pos.y - height / 2 || p.y > pos.y + height / 2) {
        return false;
    }

    if (points.size() < max_points) {
        points.push_back(p);
        return true;
    }

    if (!divided) subdivide();

    for (int i = 0; i < 4; ++i) {
        if (children[i]->insert(p)) return true;
    }
    return false;
}

void QuadTreeNode::subdivide() {

    int w = width / 2;
    int h = height / 2;

    children[0] = new QuadTreeNode(pos.x - w / 2, pos.y + h / 2, w, h, max_points);
    children[1] = new QuadTreeNode(pos.x + w / 2, pos.y + h / 2, w, h, max_points);
    children[2] = new QuadTreeNode(pos.x - w / 2, pos.y - h / 2, w, h, max_points);
    children[3] = new QuadTreeNode(pos.x + w / 2, pos.y - h / 2, w, h, max_points);
    divided = true;
}

void QuadTreeNode::rangeSearch(int rangeX, int rangeY, int range, std::vector<Point>& found_points) {
    if (pos.x - width / 2 > rangeX + range || pos.x + width / 2 < rangeX - range ||
        pos.y - height / 2 > rangeY + range || pos.y + height / 2 < rangeY - range) {
        return;
    }

    for (const Point& p : points) {
        if (std::abs(p.x - rangeX) <= range && std::abs(p.y - rangeY) <= range) {
            found_points.push_back(p);
        }
    }

    if (divided) {
        for (int i = 0; i < 4; ++i) {
            children[i]->rangeSearch(rangeX, rangeY, range, found_points);
        }
    }
}

void QuadTreeNode::exportNodeStructure(std::ofstream& file, int level) {
    for (int i = 0; i < level; ++i) file << "--";
    file << "Cuadrante (" << pos.x << ", " << pos.y << "), Ancho: " << width << ", Altura: " << height << "\n";

    for (const auto& point : points) {
        for (int i = 0; i <= level; ++i) file << "--";
        file << "Punto (" << point.x << ", " << point.y << ")\n";
    }

    if (divided) {
        for (int i = 0; i < 4; ++i) {
            children[i]->exportNodeStructure(file, level + 1);
        }
    }
}

// ------------------------------------------------------------------ QUAD TREE ------------------------------------------------------------------

QuadTree::QuadTree(int width, int height, int max_points) {
    root = new QuadTreeNode(width / 2, height / 2, width, height, max_points);
}

void QuadTree::insert(Point p) { 
    root->insert(p);// redirecion a nodo
}

void QuadTree::exportStructure(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        root->exportNodeStructure(file, 0);
        file.close();
    }
}

std::vector<Point> QuadTree::rangeSearch(int rangeX, int rangeY, int range) { 
    std::vector<Point> found_points;
    root->rangeSearch(rangeX, rangeY, range, found_points);// redirecion a nodo
    return found_points;
}