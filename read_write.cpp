#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct rgb {
#pragma once
    int r;
    int g;
    int b;
};

class convert
{
public:

    void read_file(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            throw std::runtime_error("Konnte Datei nicht öffnen!");
        }

        skip_comments_and_whitespace(file);
        file >> type;
        skip_comments_and_whitespace(file);
        file >> width >> height;
        skip_comments_and_whitespace(file);
        file >> colour_max;

        if (type != "P3") {
            throw std::runtime_error("Ungültiges Dateiformat!");
        }

        file.ignore(); // Skip single whitespace character

        std::vector<std::vector<rgb>> image(height, std::vector<rgb>(width));
        for (int i = 0; i < height; ++i) {
            file.read(reinterpret_cast<char*>(image[i].data()), width * sizeof(rgb));
        }

        picture = image;
    }

    void skip_comments_and_whitespace(std::ifstream& file) {
        char ch;
        file >> std::ws; // Skip any whitespace
        while (file.peek() == '#') { // Check for comment
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file >> std::ws; // Skip any whitespace
        }
    }

    void write_file() {
        ofstream output_file("output.ppm");
        // Headline
        output_file << type << endl;
        output_file << width << " " << height << endl;
        output_file << colour_max;
        // Picture
        for (int i = 0; i < height; i++) {
            output_file << endl;
            row.clear();
            row = picture[i];
            for (int j = 0; j < width; j++) {
                pixel = row[j];
                output_file << pixel.r << " " << pixel.g << " " << pixel.b << " ";
            } 
        }
        output_file.close();
    }

    // get and set
    vector<vector<rgb> > get_picture() {
        return picture;
    }
    void set_picture(vector<vector<rgb>> new_picture) {
        picture = new_picture;
    }

    int get_width() {
        return width;
    }
    int get_height() {
        return height;
    }
    void set_width(int new_width) {
        width = new_width;
    }
    void set_height(int new_height) {
        height = new_height;
    }

private:
    string type;
    int width;
    int height;
    int colour_max;

    rgb pixel;
    vector<vector<rgb> > picture;
    vector<rgb> row;
};



