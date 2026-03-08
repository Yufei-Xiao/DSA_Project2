

#ifndef DSA_PROJECT2_COURSE_H
#define DSA_PROJECT2_COURSE_H
#include <string>
#include<vector>
using namespace std;

class CourseSystem {
private:
    struct Course{
        string id;
        string name;
        string university;
        float drop_rate;
        float GPA;
        float course_rating;
        float professor_rating;


    };
    vector<Course> courses;
public:


};


#endif //DSA_PROJECT2_COURSE_H