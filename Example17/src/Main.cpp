#include "Application.hpp"

int main() {
    Application &application = Application::GetInstance();
    application.Run();
    return 0;
}
