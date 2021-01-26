#include <iostream>

/* Simple example of SRP violation */

class PDF {};
class Docx {};

class TextEditor {
public:
    TextEditor() = default;
    TextEditor(const std::string&);

    // Responsible for internal state and text manipulation logic
    void insertText(int position, const std::string&);
    void deleteText(int from, int size);

    // Responsible for GUI logic
    void display();
    void resizeDisplay(int width, int hight);

    // Responsible for communicating to some printing device
    // and preparing data for printing
    void print();

    // Responsible for conversions to other formats
    PDF convertToPdf();
    Docx convertToDocx();
};

int main()
{
    return 0;
}