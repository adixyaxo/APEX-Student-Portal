#include "httplib.h"
#include <string>
#include <format>
#include <cmath>
class Students
{
private:
    std::string name;
    std::string rollno;
    std::string klas;
    float CGPA;


public:
    std::string get_name() { return name; }
    std::string get_rollno() { return rollno; }
    std::string get_klas() { return klas; }
    float get_cgpa() {  return CGPA; }
    std::string about() { return R"(

    <div style="
        background:white;
        padding:25px;
        border-radius:12px;
        box-shadow:0 4px 10px rgba(0,0,0,0.2);
        width:400px;
    ">

        <h2 style="
            text-align:center;
            color:#333;
        ">
            Student Information
        </h2>

        <table style="
            width:100%;
            border-collapse:collapse;
        ">

            <tr style="background-color:#4CAF50; color:white;">
                <th style="padding:10px;">Field</th>
                <th style="padding:10px;">Details</th>
            </tr>

            <tr>
                <td style="padding:10px; border-bottom:1px solid #ddd;">Name</td>
                <td style="padding:10px; border-bottom:1px solid #ddd;">)" +
                                 name + R"(</td>
            </tr>

            <tr>
                <td style="padding:10px; border-bottom:1px solid #ddd;">Roll No</td>
                <td style="padding:10px; border-bottom:1px solid #ddd;">)" +
                                 rollno + R"(</td>
            </tr>

            <tr>
                <td style="padding:10px; border-bottom:1px solid #ddd;">Class</td>
                <td style="padding:10px; border-bottom:1px solid #ddd;">)" +
                                 klas + R"(</td>
            </tr>

            <tr>
                <td style="padding:10px;">CGPA</td>
                <td style="padding:10px;">)" +
                                 std::to_string(std::trunc((CGPA*100)/100)) + R"(</td>
            </tr>

        </table>

    </div>)"; }
    Students(std::string name, std::string rollno, std::string klas, float CGPA)
    {
        this->name = name;
        this->rollno = rollno;
        this->klas = klas;
        this->CGPA = CGPA;
    };
    ~Students() = default;
};

class strings
{
private:
public:
    strings() = default;
    std::string return_basic_html(std::string body)
    {
        std::string str = "<html><head></head><body>" + body + "</body></html>";
        return str;
    }
    ~strings() = default;
};

int main()
{

    strings String_Instance;
    Students student("Hamza", "25csu016", "12", 11.9);
    httplib::Server svr;

    svr.set_mount_point("/", "./Templates");

    svr.Get("/", [](const httplib::Request &, httplib::Response &res) { // basic route
        res.set_content("Hello, World!", "text/plain");
    });

    svr.Get("/html", [&String_Instance](const httplib::Request &, httplib::Response &res) { // basic route
        std::string body = "<h1> Namaste ji </h1>";
        std::string str = String_Instance.return_basic_html(body);
        res.set_content(str, "text/html");
    });

    svr.Get("/route", [](const httplib::Request &, httplib::Response &res) { // normal route
        res.set_content("Routes route", "text/plain");
    });

    svr.Get(R"(/files/(\d+)/(\d+))", [](const auto &req, auto &res) { // mutiple dynamic integer routes
        auto id = req.matches[1];
        auto id_2 = req.matches[2];
        res.set_content("File ID: " + std::string(id) + std::string(id_2), "text/plain");
    });

    svr.Get("/Students/:id", [&student, &String_Instance](const auto &req, auto &res) { // dynamic string route
        auto id = req.path_params.at("id");
        std::string content = String_Instance.return_basic_html(student.about());
        res.set_content(content, "text/html");
    });

    svr.listen("0.0.0.0", 8080);
}