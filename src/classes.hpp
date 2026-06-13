#ifndef CLASSES_HPP
#define CLASSES_HPP
#include "../libs/crow_all.h"
#include <string>
#include <unordered_map>
#include "../libs/json.hpp"

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
  SUBJECT(std::string name,
          std::string code,
          int credits,
          int total_internal,
          int total_external,
          int internal,
          int external,
          std::string grade);
  ~SUBJECT();
  SUBJECT();
  // getters
  const std::string &get_name() const { return name; }
  const std::string &get_code() const { return code; }
  int get_credits() const { return credits; }
  int get_total_internal() const { return total_internal; }
  int get_total_external() const { return total_external; }
  int get_internal() const { return internal; }
  int get_external() const { return external; }
  const std::string &get_grade() const { return grade; }
  // setters
  void set_name(const std::string &name) { this->name = name; }
  void set_code(const std::string &code) { this->code = code; }
  void set_credits(int credits) { this->credits = credits; }
  void set_total_internal(int total_internal) { this->total_internal = total_internal; }
  void set_total_external(int total_external) { this->total_external = total_external; }
  void set_internal(int internal) { this->internal = internal; }
  void set_external(int external) { this->external = external; }
  void set_grade(const std::string &grade) { this->grade = grade; }
};

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
  std::string password;
  std::unordered_map<std::string, SUBJECT> subjects;
  int theme;

public:
  STUDENT();
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
          std::string password,
          int theme);

  STUDENT(std::string name,
          std::string roll_no,
          std::string course,
          std::string specialization,
          int current_semester,
          std::string mobile,
          std::string university_mail,
          std::string password,
          int theme);

  ~STUDENT();

  const std::string &get_name() const { return name; }
  const std::string &get_roll_no() const { return roll_no; }
  const std::string &get_course() const { return course; }
  const std::string &get_specialization() const { return specialization; }
  int get_current_semester() const { return current_semester; }
  float get_current_cgpa() const { return current_cgpa; }
  int get_current_rank() const { return current_rank; }
  int get_credits_earned() const { return credits_earned; }
  double get_percentile() const { return percentile; }
  int get_rank_change() const { return rank_change; }
  const std::string &get_mobile() const { return mobile; }
  const std::string &get_university_mail() const { return university_mail; }
  const std::unordered_map<std::string, SUBJECT> &get_subjects() const { return subjects; }
  int get_theme() const { return theme; }

  void set_name(const std::string &name) { this->name = name; }
  void set_roll_no(const std::string &roll_no) { this->roll_no = roll_no; }
  void set_course(const std::string &course) { this->course = course; }
  void set_specialization(const std::string &specialization) { this->specialization = specialization; }
  void set_current_semester(int current_semester) { this->current_semester = current_semester; }
  void set_current_cgpa(float current_cgpa) { this->current_cgpa = current_cgpa; }
  void set_current_rank(int current_rank) { this->current_rank = current_rank; }
  void set_credits_earned(int credits_earned) { this->credits_earned = credits_earned; }
  void set_percentile(double percentile) { this->percentile = percentile; }
  void set_rank_change(int rank_change) { this->rank_change = rank_change; }
  void set_mobile(const std::string &mobile) { this->mobile = mobile; }
  void set_university_mail(const std::string &university_mail) { this->university_mail = university_mail; }
  void set_password(const std::string &password) { this->password = password; }
  void set_subjects(const SUBJECT &subject) { this->subjects.emplace(subject.get_name(), subject); }
  void set_theme(int theme) { this->theme = theme; }
  void Fetch(std::string mail= "");
  crow::mustache::context set_context();
  int Store();
  nlohmann::json to_json() const;
};

#endif
