#include "httplib.h"

int main() {

    httplib::Server svr;

    svr.set_mount_point("/", "./Templates");

    svr.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello, World!", "text/plain");
    });

    svr.Get("/route",[](const httplib::Request&, httplib::Response& res){
        res.set_content("Routes route","text/plain");
    });

    svr.Get(R"(/files/(\d+)/(\d+))", [](const auto &req, auto &res) {
        auto id = req.matches[1];
        auto id_2 = req.matches[2];
        res.set_content("File ID: " + std::string(id)+ std::string(id_2), "text/plain");
    });

     svr.Get("/users/:id", [](const auto &req, auto &res) {
        auto id = req.path_params.at("id");
        res.set_content("User ID: " + id, "text/plain");
    });


    svr.listen("0.0.0.0", 8080);
}