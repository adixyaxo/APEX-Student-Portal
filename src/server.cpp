#include <iostream>
#include "../libs/crow_all.h"
#include "server.hpp"
#include "classes.hpp"
#include <string>
#include "../libs/json.hpp"

void run_app()
{
  crow::SimpleApp app;
  STUDENT student("aditya",
                  "25csu016",
                  "Btech",
                  "Computer Science Engineering",
                  2,
                  " ",
                  " ",
                  " ",
                  1);
  SUBJECT english("English", "code", 100, 100, 100, 10, 10, "A+");
  student.set_subjects(english);
  if (student.Store() == 0)
  {
    std::cout << "\nSucessfully stored students information\n";
  }
  else
    std::cout << "\nerror encountered while storing the student values\n";

  CROW_ROUTE(app, "/")([&student]()
                       {
    auto ctx = student.set_context();
    auto page = crow::mustache::load("index.html");
    return page.render(ctx); });
  app.bindaddr("0.0.0.0").port(8080).multithreaded().run();
}
