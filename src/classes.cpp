#include "classes.hpp"
#include "../libs/json.hpp"
#include <fstream>
#include <iostream>
#include "../libs/crow_all.h"

using json = nlohmann::json;

SUBJECT::SUBJECT(std::string name, std::string code, int credits, int total_internal, int total_external, int internal, int external, std::string grade)
    : name(name),
      code(code),
      credits(credits),
      total_internal(total_internal),
      total_external(total_external),
      internal(internal),
      external(external),
      grade(grade)
{
}
SUBJECT::SUBJECT():name(""),code(""),credits(0),total_internal(0),total_external(0),internal(0),external(0),grade("")
{
}
SUBJECT::~SUBJECT()
{
}

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
                 std::string password,
                 int theme)
    : name(name),
      roll_no(roll_no),
      course(course),
      specialization(specialization),
      current_semester(current_semester),
      current_cgpa(current_cgpa),
      current_rank(current_rank),
      credits_earned(credits_earned),
      percentile(percentile),
      rank_change(rank_change),
      mobile(mobile),
      university_mail(university_mail),
      password(password),
      theme(theme)
{
}

STUDENT::STUDENT(std::string name,
                 std::string roll_no,
                 std::string course,
                 std::string specialization,
                 int current_semester,
                 std::string mobile,
                 std::string university_mail,
                 std::string password,
                 int theme)
    : STUDENT(name, roll_no, course, specialization, current_semester, 0.0f, 0, 0, 0.0, 0, mobile, university_mail, password, theme)
{
}

STUDENT::~STUDENT()
{
}

json STUDENT::to_json() const
{
  json j;
  j["name"] = name;
  j["roll_no"] = roll_no;
  j["course"] = course;
  j["specialization"] = specialization;
  j["current_semester"] = current_semester;
  j["current_cgpa"] = current_cgpa;
  j["current_rank"] = current_rank;
  j["credits_earned"] = credits_earned;
  j["percentile"] = percentile;
  j["rank_change"] = rank_change;
  j["mobile"] = mobile;
  j["university_mail"] = university_mail;
  j["password"] = password;
  j["theme"] = theme;

  json subjects_json;
  for (const auto &[subject_name, subject] : subjects)
  {
    subjects_json[subject_name] = {
        {"name", subject.get_name()},
        {"credits", subject.get_credits()},
        {"total_internal", subject.get_total_internal()},
        {"total_external", subject.get_total_external()},
        {"internal", subject.get_internal()},
        {"external", subject.get_external()},
        {"grade", subject.get_grade()}};
  }
  j["subjects"] = subjects_json;

  return j;
}

int STUDENT::Store()
{
  // we will implement this function to store the student data in a json file in the database folder
  std::string Json_data = this->to_json().dump();
  std::string path = "Database/" + this->university_mail + ".json";
  std::ofstream file(path);
  file << Json_data;
  file.close();
  return 0;
}

void STUDENT::Fetch()
{
  std::string filename = university_mail + ".json";
  std::string path = filename;
  path = "Database/" + filename;
  std::ifstream file(path);

  if (!file.is_open())
  {
    file.clear();
    file.open(path);
  }

  if (!file.is_open())
  {
    std::cerr << "Could not open student data file: " << filename << '\n';
    return;
  }

  json j;
  try
  {
    file >> j;
  }
  catch (const json::exception &error)
  {
    std::cerr << "Could not parse student data file: " << path << " (" << error.what() << ")\n";
    return;
  }

  name = j["name"].get<std::string>();
  roll_no = j["roll_no"].get<std::string>();
  course = j["course"].get<std::string>();
  specialization = j["specialization"].get<std::string>();
  current_semester = j["current_semester"].get<int>();
  current_cgpa = j["current_cgpa"].get<float>();
  current_rank = j["current_rank"].get<int>();
  credits_earned = j["credits_earned"].get<int>();
  percentile = j["percentile"].get<double>();
  rank_change = j["rank_change"].get<int>();
  mobile = j["mobile"].get<std::string>();
  university_mail = j["university_mail"].get<std::string>();
  password = j["password"].get<std::string>();
  theme = j["theme"].get<int>();

  for (const auto &[subject_name, subject_json] : j["subjects"].items())
  {
    SUBJECT subject;
    subject.set_code(subject_json["code"].get<std::string>());
    subject.set_name(subject_json["name"].get<std::string>());
    subject.set_grade(subject_json["grade"].get<std::string>());
    subject.set_credits(subject_json["credits"].get<int>());
    subject.set_total_internal(subject_json["total_internal"].get<int>());
    subject.set_total_external(subject_json["total_external"].get<int>());
    subject.set_internal(subject_json["internal"].get<int>());
    subject.set_external(subject_json["external"].get<int>());
    subjects.emplace(subject_name, subject);
  }
}

crow::mustache::context STUDENT::set_context(){
  crow::mustache::context ctx;
  ctx["name"] = name;
  ctx["roll_no"] = roll_no;
  ctx["course"] = course;
  ctx["specialization"] = specialization;
  ctx["current_semester"] = current_semester;
  ctx["current_cgpa"] = current_cgpa;
  ctx["current_rank"] = current_rank;
  ctx["credits_earned"] = credits_earned;
  ctx["percentile"] = percentile;
  ctx["rank_change"] = rank_change;
  ctx["mobile"] = mobile;
  ctx["university_mail"] = university_mail;
  ctx["theme"] = theme;
  return ctx;
};