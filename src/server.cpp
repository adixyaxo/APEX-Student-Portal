#include <iostream>
#include "../libs/crow_all.h"
#include "classes.hpp"

void run_app(){
  crow::SimpleApp app;

  CROW_ROUTE(app, "/")([]()
                       {
                        auto page = crow::mustache::load("index.html");
                        crow::mustache::context ctx;
                        return page.render(); });

  app.bindaddr("0.0.0.0").port(8080).multithreaded().run();
}