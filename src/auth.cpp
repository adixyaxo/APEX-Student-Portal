#include <iostream>
#include "../libs/crow_all.h"
#include "classes.hpp"

void Register_User(const crow::request& req, crow::response& res) {
  (void)req;
  // Extract user details from the request body (e.g., JSON)
  // Validate the input data
  // Create a new STUDENT object and store it in a database or in-memory data structure
  // Send an appropriate response back to the client
  res.code = 501;
  res.set_header("Content-Type", "application/json");
  res.write("{\"message\":\"Registration endpoint not implemented\"}");
  res.end();
}
