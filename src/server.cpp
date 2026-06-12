#include <iostream>
#include "../libs/crow_all.h"
#include "server.hpp"
#include "classes.hpp"
#include <string>

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
    student.Student_Fetch("data.json");
  CROW_ROUTE(app, "/")([&student]()
                       {
    auto page = crow::mustache::load("index.html");
    crow::mustache::context ctx;
    ctx["theme"] = student.get_theme();
    return page.render(ctx); });
  app.bindaddr("0.0.0.0").port(8080).multithreaded().run();
}
