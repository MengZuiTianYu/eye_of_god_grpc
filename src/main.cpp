#include <iostream>
#include "grpc_eye_server.h"

int main(int argc, char** argv) {
    grpc_RunServer(NULL,"0.0.0.0:50052");
    return 0;
}
