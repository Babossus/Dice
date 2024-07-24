#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>

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
        // platz reservieren
        picture.reserve(height);
        row.reserve(width);
        
        // adresse erstellen
        srand(std::time(nullptr));
        int rnd = rand() % 5;;
        rnd++;
        string end = ".ppm";

        stringstream path_temp;
        path_temp << rnd << end;
        string path = path_temp.str();
        //cout << rnd << endl;

        // öffnen und schauen ob vorhanden
        ifstream input_file("1.ppm"/*path*/);
        if (!input_file.is_open()) {
            cerr << "Fehler beim Öffnen der Datei." << endl;
            return;
        }

        // Headline
        input_file >> type;
        input_file >> width >> height;
        input_file >> colour_max;

        // Picture
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                input_file >> pixel.r >> pixel.g >> pixel.b;
                row.push_back(pixel);
            }
            picture.push_back(row);
            row.clear();
        }
        input_file.close();
    }

    void skip_comments_and_whitespace(std::ifstream& file) {
        char ch;
        file >> std::ws;
        while (file.peek() == '#') {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            file >> std::ws;
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



