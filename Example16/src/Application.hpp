#pragma once

class Application {
public:
    void Run();

    static Application &GetInstance();

private:
    bool mWireframe = false;
};
