#include <iostream>
#include "../libs/crow_all.h"
#include "server.hpp"
#include "classes.hpp"
#include <string>
#include "../libs/json.hpp"

void run_app()
{
  crow::SimpleApp app;
  STUDENT student;
  student.Fetch("aditya0dagar@gmail.com");

  CROW_ROUTE(app, "/")([&student]()
                       {
    auto ctx = student.set_context();
    auto page = crow::mustache::load("index.html");
    return page.render(ctx); });
  CROW_ROUTE(app, "/profile")([&student]()
                              {
    auto ctx = student.set_context();
    auto page = crow::mustache::load("profile.html");
    return page.render(ctx); });
  CROW_ROUTE(app, "/about")([&student]()
                            {
    auto ctx = student.set_context();
    auto page = crow::mustache::load("about.html");
    return page.render(ctx); });

  CROW_ROUTE(app, "/new_subject").methods(crow::HTTPMethod::POST)([&student](const crow::request &req)
                                                                  {
    auto ctx = student.set_context();
    auto params = req.get_body_params();
    std::string name = params.get("name");
    std::cout<<name<<std::endl;
    return name; });

  app.bindaddr("0.0.0.0").port(8080).multithreaded().run();
}
