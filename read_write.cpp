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

    void read_file() {
        // platz reservieren
        picture.reserve(height);
        row.reserve(width);

        // öffnen und schauen ob vorhanden
        ifstream input_file("input.ppm");
        if (!input_file.is_open()) {
            cerr << "Fehler beim Öffnen der Datei." << endl;
            return;
        }

        // Headline
        input_file >> type;
        input_file >> width >> height;
        input_file >> colour_max;

        // Picture
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                input_file >> pixel.r >> pixel.g >> pixel.b;
                row.push_back(pixel);
            }
            picture.push_back(row);
            row.clear();
        }
        input_file.close();
    }

    void write_file() {
        ofstream output_file("output.ppm");
        // Headline
        output_file << type << endl;
        output_file << width << " " << height << endl;
        output_file << colour_max;
        // Picture
        for (int i = 0; i < width; i++) {
            output_file << endl;
            row.clear();
            row = picture[i];
            for (int j = 0; j < row.size(); j++) {
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



