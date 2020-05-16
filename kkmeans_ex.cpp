// The contents of this file are in the public domain. See LICENSE_FOR_EXAMPLE_PROGRAMS.txt
/*
    This is an example illustrating the use of the kkmeans object 
    and spectral_cluster() routine from the dlib C++ Library.

    The kkmeans object is an implementation of a kernelized k-means clustering 
    algorithm.  It is implemented by using the kcentroid object to represent 
    each center found by the usual k-means clustering algorithm.  

    So this object allows you to perform non-linear clustering in the same way 
    a svm classifier finds non-linear decision surfaces.  
    
    This example will make points from 3 classes and perform kernelized k-means 
    clustering on those points.  It will also do the same thing using spectral 
    clustering.

    The classes are as follows:
        - points very close to the origin
        - points on the circle of radius 10 around the origin
        - points that are on a circle of radius 4 but not around the origin at all
*/

#include <iostream>
#include <vector>
#include<unordered_map>
#include <fstream>

#include <dlib/clustering.h>
#include <dlib/rand.h>

using namespace std;
using namespace dlib;

int main(int argc, char* argv[])
{
    bool print = true;
    if (argc != 3 && argc != 4) {
        std::cout << "Usage:" << std::endl;
        std::cout << "\tkkmeans number_of_clusters sample_file <flag_tofile>";
        return 0;
    } else if (argc == 4) print = false;

    int number_of_clusters = atoi(argv[1]);
    // Here we declare that our samples will be 2 dimensional column vectors.  
    // (Note that if you don't know the dimensionality of your vectors at compile time
    // you can change the 2 to a 0 and then set the size at runtime)
    typedef matrix<double,2,1> sample_type;

    // Now we are making a typedef for the kind of kernel we want to use.  I picked the
    // radial basis kernel because it only has one parameter and generally gives good
    // results without much fiddling.
    typedef radial_basis_kernel<sample_type> kernel_type;


    // Here we declare an instance of the kcentroid object.  It is the object used to 
    // represent each of the centers used for clustering.  The kcentroid has 3 parameters 
    // you need to set.  The first argument to the constructor is the kernel we wish to 
    // use.  The second is a parameter that determines the numerical accuracy with which 
    // the object will perform part of the learning algorithm.  Generally, smaller values 
    // give better results but cause the algorithm to attempt to use more dictionary vectors 
    // (and thus run slower and use more memory).  The third argument, however, is the 
    // maximum number of dictionary vectors a kcentroid is allowed to use.  So you can use
    // it to control the runtime complexity.  
    kcentroid<kernel_type> kc(kernel_type(0.001),0.006, 200/(number_of_clusters*8));

    // Now we make an instance of the kkmeans object and tell it to use kcentroid objects
    // that are configured with the parameters from the kc object we defined above.
    kkmeans<kernel_type> test(kc);

    std::vector<sample_type> samples;
    std::vector<sample_type> initial_centers;

    sample_type m;

    std::ifstream sampleFile(argv[2]);
    std::string sampleLine;
    while(sampleFile >> sampleLine) {
        try {
            m(0) = atof(sampleLine.substr(0, sampleLine.find(';')).c_str());
            m(1) = atof(sampleLine.substr(sampleLine.find(';') + 1, sampleLine.size() - sampleLine.find(';')).c_str());
            samples.push_back(m);
        } catch(...) {
            std::cout << "Error in parsing sample data";
            return 1;
        }
    }

    // tell the kkmeans object we made that we want to run k-means with k set to 3. 
    // (i.e. we want 3 clusters)
    test.set_number_of_centers(number_of_clusters);

    // You need to pick some initial centers for the k-means algorithm.  So here
    // we will use the dlib::pick_initial_centers() function which tries to find
    // n points that are far apart (basically).  
    pick_initial_centers(number_of_clusters, initial_centers, samples, test.get_kernel());

    // now run the k-means algorithm on our set of samples.  
    test.train(samples,initial_centers);

    std::string one;
    std::vector<std::string> vec_res;
    std::unordered_map<int, int> counters;
    while(std::cin >> one) {
        try {
            double x = atof(one.substr(0, one.find(';')).c_str());
            double y = atof(one.substr(one.find(';') + 1, one.size() - one.find(';')).c_str());
            unsigned long cluster = test({x, y});
            std::string res = to_string(x) + ";" + to_string(y) + ";" + to_string(cluster);
            counters[cluster]++;
            vec_res.emplace_back(res);
        } catch(...) {
            std::cout << "Error in parsing test data";
            return 1;
        }
    }
    if (print) {
        for (const auto& a : vec_res)
            std::cout << a << std::endl;
    } else {
        std::ofstream fileO("./results.txt");
        fileO << counters.size() << std::endl;
        for (const auto& a : counters)
            fileO << a.first << " " << a.second << std::endl;
        fileO.close();
    }
}



