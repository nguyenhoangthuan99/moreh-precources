// KMeans.h
#ifndef KMEANS_H
#define KMEANS_H

#include <vector>
#include "Point.h"

class KMeans {
private:
    std::vector<Point> data_points;
    std::vector<Point> centroids;
    std::vector<int> points_cluster;
    int k;

public:
    KMeans(int num_points, int k);
    void run(int max_iterations);

private:
    void initializeCentroids();
    void generateRandomDataPoints(int num_points);
    void assignToClusters();
    double updateCentroids();
    double calculateDistance(const Point& p1, const Point& p2);
};

#endif // KMEANS_H
