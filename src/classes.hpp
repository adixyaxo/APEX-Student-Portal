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
  std::string password;

public:
  student(std::string name,
          std::string roll_no,
          std::string course,
          std::string specialization,
          int current_semester,
          float current_cgpa,
          int current_rank,
          int credits_earned,
          double percentile,
          int rank_change,
          std::string mobile,
          std::string university_mail,
          std::string password);
  ~student();
};

class SUBJECT
{
private:
  std::string name;
  std::string code;
  int credits;
  int total_internal;
  int total_external;
  int internal;
  int external;
  std::string grade;

public:
  SUBJECT(std::string name, std::string code, int credits, int total_internal, int total_external, int internal, int external, std::string grade);
  ~SUBJECT();
};

#endif