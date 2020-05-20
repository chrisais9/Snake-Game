/* 
 * title: Snake-Game.h
 * 
 */

#ifndef SNAKE_GAME
#define SNAKE_GAME

#include <algorithm>
#include <vector>
#include <deque>
#include <queue>
#include <set>
#include <cstdlib>
#include <ctime>

enum Item{
    ERROR,
    EMPTY,
    WALL,
    IMWALL,
    GATE,
    GROWTH,
    POISON,
    SNAKE,
};

struct Point{
    int x, y;
    Point(int x=0, int y=0){
        this->x = x;
        this->y = y;
    }
    bool isValid(int width, int height) const{
        return x >= 0 && y >= 0 && x < width && y < height;
    }
    Point& operator+=(const Point& p){
        x += p.x;
        y += p.y;
        return *this;
    }
    Point operator+(const Point& p) const{
        Point ret = *this;
        ret += p;
        return ret;
    }
    bool operator<(const Point& p) const{
        if(x == p.x)
            return y < p.y;
        return x < p.x;
    }
    bool operator>(const Point& p) const{
        if(x == p.x)
            return y > p.y;
        return x > p.x;
    }
    bool operator==(const Point& p) const{
        return x == p.x && y == p.y;
    }
};

struct IndexedPoint{
    int idx;
    Point p;
    bool operator<(const IndexedPoint& ip) const{
        return idx < ip.idx;
    }
    bool operator>(const IndexedPoint& ip) const{
        return idx > ip.idx;
    }
    bool operator==(const IndexedPoint& ip) const{
        return idx == ip.idx;
    }
};

struct MapManager{
    int width, height;
    std::vector<std::vector<Item>> gameMap;

    MapManager(int width=0, int height=0){
        this->width = width;
        this->height = height;
        gameMap.resize(height);
        for(int y = 0; y < height; ++y)
            gameMap[y].resize(width, EMPTY);
    }
    Item get(int x, int y) const{
        if(x < 0 || y < 0 || x >= width || y >= height)
            return ERROR;
        return gameMap[y][x];
    }
    Item get(Point p) const{
        return get(p.x, p.y);
    }
    void set(int x, int y, Item v){
        if(x < 0 || y < 0 || x >= width || y >= height)
            return;
        gameMap[y][x] = v;
    }
    void set(Point p, Item v){
        set(p.x, p.y, v);
    }
};

const Point DIRECTIONS[4] = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

class RandomGenerator{
private:
public:
    RandomGenerator(){
        srand((unsigned)time(NULL));
    }
    int getRandom(int s, int e){
        return rand() % (e - s + 1) + s;
    }
};

class Snake{
private:
    int length = 3;
    int direction = 0;
    int portalRemaining = 0;
    std::deque<Point> snakeBody;
    std::queue<Point> eraseQueue, insertQueue;
    std::set<Point> snakePoints;
    
    Point getNewHead();
    void pushFront(Point body);
    void popBack();
    bool checkValidity(MapManager& gameMap);

    void generalMove(Point newH);
    void growthMove(Point newH);
    void poisonMove(Point newH);
public:
    Snake(){}
    Snake(MapManager& gameMap, Point headPoint={0, 0}, int length=3, int direction=0);

    Item move(int direction, MapManager& gameMap, std::vector<Point>& portals);

    Point getHead();
    bool checkPoint(Point p);
    bool isInPortal();
};

class GameRunner{
private:
    MapManager gameMap;
    Snake snake;

    int frames = 0;

    const int ITEM_MAX_TIME = 10;
    const int MAX_NUMBER_OF_GROWTH = 3;
    const int MAX_NUMBER_OF_POISON = 3;

    RandomGenerator randomGenerator;

    int totalNumberOfItemCandidates = 0;
    std::set<IndexedPoint> itemsCandidates;
    std::vector<Point> portalCandidates;

    std::queue<std::pair<IndexedPoint, int>> growthTimeQ, poisonTimeQ;
    std::multiset<Point> itemsUsed;
    int numberOfGrowth = 0;
    int numberOfPoison = 0;

    int portalTime = -1;
    std::vector<Point> portals;

    Point getRandomItemPoint(std::queue<std::pair<IndexedPoint, int>>& timeQ);

    void updateGrowth();
    void updatePoison();
    void updatePortal();
public:
    GameRunner(const MapManager& gameMap, Point startPoint, int length=3, int direction=0);

    bool nextFrame(int direction);
    const MapManager& getMap();
};

#endif