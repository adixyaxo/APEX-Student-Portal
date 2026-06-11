#include <string>
#include <classes.hpp>
#include <vector>
#include <unordered_map>

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

SUBJECT::SUBJECT(std::string name, std::string code, int credits, int total_internal, int total_external, int internal, int external, std::string grade)
{
  this->name = name;
  this->code = code;
  this->credits = credits;
  this->total_internal = total_internal;
  this->total_external = total_external;
  this->internal = internal;
  this->external = external;
  this->grade = grade;
}

SUBJECT::~SUBJECT()
{
}

class STUDENT
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
  std::unordered_map<std::string, SUBJECT> subjects;

public:
  // getters
  std::string get_name() { return name; }
  std::string get_roll_no() { return roll_no; }
  std::string get_course() { return course; }
  std::string get_specialization() { return specialization; }
  int get_current_semester() { return current_semester; }
  float get_current_cgpa() { return current_cgpa; }
  int get_current_rank() { return current_rank; }
  int get_credits_earned() { return credits_earned; }
  double get_percentile() { return percentile; }
  int get_rank_change() { return rank_change; }
  std::string get_mobile() { return mobile; }
  std::string get_university_mail() { return university_mail; }
  std::unordered_map<std::string, SUBJECT> get_subjects() { return subjects; }
  // setters
  void set_name(std::string name) { this->name = name; }
  void set_roll_no(std::string roll_no) { this->roll_no = roll_no; }
  void set_course(std::string course) { this->course = course; }
  void set_specialization(std::string specialization) { this->specialization = specialization; }
  void set_current_semester(int current_semester) { this->current_semester = current_semester; }
  void set_current_cgpa(float current_cgpa) { this->current_cgpa = current_cgpa; }
  void set_current_rank(int current_rank) { this->current_rank = current_rank; }
  void set_credits_earned(int credits_earned) { this->credits_earned = credits_earned; }
  void set_percentile(double percentile) { this->percentile = percentile; }
  void set_rank_change(int rank_change) { this->rank_change = rank_change; }
  void set_mobile(std::string mobile) { this->mobile = mobile; }
  void set_university_mail(std::string university_mail) { this->university_mail = university_mail; }
  void set_subjects(std::unordered_map<std::string, SUBJECT> subjects) { this->subjects = subjects; }
  STUDENT(std::string name,
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
          std::unordered_map<std::string, SUBJECT> subjects);
  ~STUDENT();
};
STUDENT::STUDENT(std::string name,
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
                 std::unordered_map<std::string, SUBJECT> subjects)
{
  this->name = name;
  this->roll_no = roll_no;
  this->course = course;
  this->specialization = specialization;
  this->current_semester = current_semester;
  this->course = course;
  this->current_cgpa = current_cgpa;
  this->current_rank = current_rank;
  this->credits_earned = credits_earned;
  this->percentile = percentile;
  this->rank_change = rank_change;
  this->mobile = mobile;
  this->university_mail = university_mail;
  this->subjects = subjects;
}
