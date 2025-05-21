#pragma once
#include "fs.hpp"

class UI {
public:
    UI(FileManager& fm);
    void run();
private:
    FileManager& fm;
    void draw();
    void draw_preview(const std::string& path);
};
