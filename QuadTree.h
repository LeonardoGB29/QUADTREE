#include <vector>
#include <iostream>
#include <fstream>

// --------------------------- NODOS DEL QUAD TREE ----------------------------

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

class QuadTreeNode {

public:

    Point pos;
    int width, height;
    int max_points;
    bool divided;

    std::vector<Point> points;
    QuadTreeNode* children[4];

    QuadTreeNode(int x, int y, int w, int h, int max_points);
    bool insert(Point p);
    void subdivide();
    void exportNodeStructure(std::ofstream& file, int level);
    void rangeSearch(int rangeX, int rangeY, int range, std::vector<Point>& found_points);
};

// --------------------------------- QUAD TREE ---------------------------------


class QuadTree {
public:

    QuadTreeNode* root;
    QuadTree(int width, int height, int max_points);
    void insert(Point p);
    void exportStructure(const std::string& filename);
    std::vector<Point> rangeSearch(int rangeX, int rangeY, int range);
};