#define CROW_MAIN
#include <crow.h>

#include "wheels.hpp"

int main() {
  // Create web application.
  auto app = crow::SimpleApp{};

  // Register routes.
  CROW_ROUTE(app, "/artists/")
      .methods(crow::HTTPMethod::GET,
               crow::HTTPMethod::POST)([&](const crow::request& request) {
        switch (request.method) {
          case crow::HTTPMethod::GET: {
            return "List";
          }
          case crow::HTTPMethod::POST: {
            return "Create";
          }
          default: {
            UNREACHABLE();
          }
        }
      });
  CROW_ROUTE(app, "/artists/<int>/")
      .methods(
          crow::HTTPMethod::GET, crow::HTTPMethod::PATCH,
          crow::HTTPMethod::DELETE)([&](const crow::request& request, int id) {
        switch (request.method) {
          case crow::HTTPMethod::GET: {
            return "Retrieve " + std::to_string(id);
          }
          case crow::HTTPMethod::PATCH: {
            return "Update " + std::to_string(id);
          }
          case crow::HTTPMethod::DELETE: {
            return "Destroy " + std::to_string(id);
          }
          default: {
            UNREACHABLE();
          }
        }
      });

  // Run.
  app.port(18080).run();
}
