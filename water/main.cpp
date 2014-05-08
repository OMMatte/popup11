#include <iostream>
#include <iomanip>
#include <math.h>
#include <vector>

class Point {
public:
    int x;
    int y;
    
    Point(int x, int y) : x(x), y(y) {}
};

double findDistanceToSegment(Point linePoint1, Point linePoint2, Point point) {
    double x1 = linePoint1.x;
    double y1 = linePoint1.y;
    double x2 = linePoint2.x;
    double y2 = linePoint2.y;
    double px = point.x;
    double py = point.y;
    
    double diffX = x2 - x1;
    double diffY = y2 - y1;
    if ((diffX == 0) && (diffY == 0)) {
        diffX = px - x1;
        diffY = py - y1;
        return sqrt(diffX * diffX + diffY * diffY);
    }
    
    double t = ((px - x1) * diffX + (py - y1) * diffY) / (diffX * diffX + diffY * diffY);
    
    if (t < 0) {
        diffX = px - x1;
        diffY = py - y1;
    }
    else if (t > 1) {
        diffX = px - x2;
        diffY = py - y2;
    }
    else {
        diffX = px - (x1 + t * diffX);
        diffY = py - (y1 + t * diffY);
    }
    
    return sqrt(diffX * diffX + diffY * diffY);
}

double pointsComparedToLines(std::vector<Point> points, std::vector<Point> lines) {
    double smallestDistance = -1;
    double distance;
    for(Point point: points) {
        for(int i = 0; i < lines.size(); i++) {
            Point linePoint1 = lines[i];
            Point linePoint2 = lines[(i+1) % lines.size()];
            distance = findDistanceToSegment(linePoint1, linePoint2, point);
            if(smallestDistance == -1 || distance < smallestDistance) {
                smallestDistance = distance;
            }
        }
    }
    return smallestDistance;
}

double findSmallestDistance(std::vector<Point> innerPol, std::vector<Point> outerPol) {
    double distance1 = pointsComparedToLines(innerPol, outerPol);
    double distance2 = pointsComparedToLines(outerPol, innerPol);
    
    if(distance1 < distance2) {
        return distance1;
    } else {
        return distance2;
    }
}

int main() {
    int testcases, innerCount, outerCount, x, y;
    
    scanf("%i", &testcases);
    
    for(int t = 0; t < testcases; t++) {
        std::vector<Point> innerPol;
        std::vector<Point> outerPol;
        scanf("%i", &innerCount);
        for(int i = 0; i < innerCount; i++) {
            scanf("%i %i", &x, &y);
            innerPol.push_back(Point(x, y));
        }
        scanf("%i", &outerCount);
        for(int i = 0; i < outerCount; i++) {
            scanf("%i %i", &x, &y);
            outerPol.push_back(Point(x, y));
        }
        
        double diameter = findSmallestDistance(innerPol, outerPol);
        std::cout << std::setprecision(8) << diameter/2.0 << std::endl;
        //printf("%.8f\n", diameter/2);
    }
    return 0;
}