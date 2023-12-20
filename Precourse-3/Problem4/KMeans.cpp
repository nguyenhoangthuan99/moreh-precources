// KMeans.cpp
#include "KMeans.h"
#include "Point.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <random>

// TODO: Fix the random seed to ensure consistent results across different program executions.

KMeans::KMeans(int num_points, int k) : k(k) {
    generateRandomDataPoints(num_points);
    initializeCentroids();
}

void KMeans::initializeCentroids() {
     // TODO: Implement this function
    // Initialize the centroids of clusters randomly.
    srand(42);
    std::vector<Point> vec;
    for(int i=0;i<k;i++){
        vec.push_back(this->data_points[i]);
    }
    this->centroids = vec;
    std::size_t l = this->data_points.size();
    for (std::size_t i =0;i<l;i++){
        this->points_cluster.push_back(0);
    }
    
}

double fRand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

void KMeans::generateRandomDataPoints(int num_points) {
    // TODO: Implement this function
    // Generate a given number of random data points within a specified range ( 0< x, y<50)
    srand(42);
    double min = 0, max = 50;
    std::vector<Point> vec;
    for (int i = 0 ; i< num_points;i++){
        Point p = Point(fRand(min,max),fRand(min,max));
        vec.push_back(p);
    }
    this->data_points = vec;
    this->epsilon = 1e-3; // minimum centroids distance change between 2 iteration to decide stop algorithm
    this->stop = false; // decide to stop algorithm or not

}

void KMeans::assignToClusters() {
    // TODO: Implement this function
    // Assign each point to a cluster of the nearest centroid
    for (std::size_t i =0; i <this->data_points.size();i++){
        double min_dis = 1e9;
        int cluster = 0;
        for (size_t j=0 ;j<this->centroids.size();j++){
            double dist = this->calculateDistance(this->data_points[i],this->centroids[j]);
             if (dist < min_dis){
                min_dis = dist;
                cluster = j;
             }
        }
        this->points_cluster[i] = (int)cluster;
        
    }
}

void KMeans::updateCentroids() {
    // TODO: Implement this function
    // Update the centroids of clusters based on the current assignment of data points.
    double sum = 0;
    for (int i=0;i<this->k;i++){
        double sum_x =0, sum_y=0,total=0;
        for (std::size_t j =0;j<this->data_points.size();j++){
            if(points_cluster[j] == i){
                sum_x+= this->data_points[j].x;
                sum_y+= this->data_points[j].y;
                total+=1;
            }
        }
        Point p = Point(sum_x/total, sum_y/total);
        sum += this->calculateDistance(p,this->centroids[i]);
        this->centroids[i] = p;

    }
    this->stop = sum < this->epsilon;
}

double KMeans::calculateDistance(const Point& p1, const Point& p2) {
    return std::sqrt(std::pow(p1.x - p2.x, 2) + std::pow(p1.y - p2.y, 2));
}

void KMeans::run(int max_iterations) {
    // TODO: Implement K-means algorithm and print the coordinates of each cluster centroid After the maximum number of iterations
    for (int i=0;i< max_iterations;i++){
        this->assignToClusters();
        this->updateCentroids();
        std::cout<<"Iteration "<<i<<"\n";
        std::cout<<"Centroid points :[";
        for (auto p :this->centroids){
            std::cout<< "("<< p.x<<"," <<p.y  <<"), ";
        }
        std::cout<<"]\n";

        std::cout<<"------------------------------------\n";
        if(this->stop){
            std::cout<< "centroids doesn't change significantly, stop algorithm!\n";
            break;
        }
    }

}
