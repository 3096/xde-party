#include "app.hpp"

extern "C" {

void userAppInit() {
    auto rc = Result{};
    if (R_SUCCEEDED(rc = accountInitialize(AccountServiceType_Application))) return;
    if (R_SUCCEEDED(rc = accountInitialize(AccountServiceType_System))) return;
    if (R_FAILED(rc = accountInitialize(AccountServiceType_Administrator))) fatalThrow(rc);
}

void userAppExit() { accountExit(); }

}  // extern "C"

int main() { Application::run(); }
