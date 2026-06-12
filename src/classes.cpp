#include "classes.hpp"
#include "../libs/json.hpp"
#include <fstream>
#include <iostream>

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

int STUDENT::Student_Fetch(const std::string &filename)
{
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
    return 1;
  }

  json j;
  try
  {
    file >> j;
  }
  catch (const json::exception &error)
  {
    std::cerr << "Could not parse student data file: " << path << " (" << error.what() << ")\n";
    return 2;
  }

  std::unordered_map<std::string, std::string> mp;

  for (auto &[key, value] : j.items())
  {
    mp[key] = value.dump();
  }

  for (const auto &[key, value] : mp)
  {
    std::cout << key << " : " << value << '\n';
  }

  return 0;
}
