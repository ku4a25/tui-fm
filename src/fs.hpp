#pragma once
#include <string>
#include <vector>
#include <filesystem>

struct File {
    std::string name;
    bool is_dir;
};

class FileManager {
public:
    FileManager(const std::string& path);
    void load();
    void up();
    void enter();
    void back();
    void scroll(int delta);
    bool is_image(const std::string& path) const;

    std::vector<File> files;
    int selected = 0;
    int scroll_offset = 0;
    std::string current_path;
};
