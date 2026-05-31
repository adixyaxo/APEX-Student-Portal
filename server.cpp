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

    svr.listen("0.0.0.0", 8080);
}