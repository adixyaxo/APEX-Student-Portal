#include <iostream>
#include "httplib.h"

int main() {
    httplib::Server svr;



    svr.listen("0.0.0.0",8080,0);


    return 0;
}