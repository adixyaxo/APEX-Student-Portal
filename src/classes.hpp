#ifndef CLASSES
#define CLASSES
#include <string>

class student
{
private:
std::string name;
std::string roll_no;
std::string course;
std::string specialization;
int current_semester;
float current_cgpa;
int current_rank;
int credits_earned;
double percentile;
int rank_change;
std::string mobile;
std::string university_mail;


public:
  student();
  ~student();
};

#endif CLASSES