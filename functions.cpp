#include <iostream>
#include <fstream>

using namespace std;

static char line[30000];

string getInput() {

    string source;
    char choice;
    string path;

    bool input = false;

    cout << "HELLO AND WELCOME TO THE BRAINF*CK INTERPRETER & TRANSLATOR!" << endl << endl;
    cout << "Do you want to upload source code from the file? Y/N" << endl;
    cin >> choice;
    while (!input) {
        if (choice == 'Y') {
            cout << endl << "Specify the path tp the file or enter '*' to compile default file (Fibonacci numbers): "
                 << endl;
            cin >> path;
            if (path == "*") path = "input.txt";
            ifstream in(path);
            string inputFromFile((istreambuf_iterator<char>(in)),
                                 istreambuf_iterator<char>());
            source = inputFromFile;
            cout << endl << endl << "SOURCE CODE: " << endl << endl;
            cout << source << endl << endl;
            input = true;
        } else if (choice == 'N') {
            cout << endl << "Enter your own code: " << endl;
            cin >> source;
            input = true;
        } else {
            cout << "Choose between Y or N" << endl;
            cin >> choice;
        }
    }

    return source;

}

void interpreter(string source) {

    cout << endl << "OUTPUT: " << endl << endl;

    unsigned int pointer = 0;
    int nesting = 0;

    for (int i = 0; i < source.size(); i++) {

        switch (source[i]) {

            case '>':
                pointer++;
                break;

            case '<':
                pointer--;
                break;

            case '+':
                line[pointer]++;
                break;

            case '-':
                line[pointer]--;
                break;

            case '.':
                cout << line[pointer];
                break;

            case ',':
                cin >> line[pointer];
                break;

            case '[':
                nesting = 1;
                if (line[pointer] == 0)
                    while (nesting > 0) {
                        i++;
                        if (source[i] == '[') nesting++;
                        else if (source[i] == ']') nesting--;
                    }
                break;

            case ']':
                nesting = 1;
                if (line[pointer] != 0)
                    while (nesting > 0) {
                        i--;
                        if (source[i] == '[') nesting--;
                        else if (source[i] == ']') nesting++;
                    }
                break;

            default:
                break;
        }
    }

}

void translator(string source) {

    cout << endl << endl << endl << "TRANSLATED: " << endl << endl;

    ofstream outputFile;
    outputFile.open("translated.cpp");
    int nest = 1;
    int num = 0, num2 = 0;

    string output = "";

    cout
            << "#include <iostream>\n#include <fstream>\n\nusing namespace std;\n\nint main() {\n\n    char line[30000] = { 0 };\n    int ptr = 0;\n\n";
    outputFile
            << "#include <iostream>\n#include <fstream>\n\nusing namespace std;\n\nint main() {\n\n    char line[30000] = { 0 };\n    int ptr = 0;\n\n";

    for (int i = 0; i < source.size(); i++) {

        switch (source[i]) {

            case '>':
                num = 0;
                num2++;
                if (i < source.size() - 1 && source[i + 1] != '>') {
                    for (int j = 0; j < nest; j++) {
                        cout << "    ";
                        outputFile << "    ";
                    }
                    if (num2 == 1) {
                        cout << "ptr++;\n";
                        outputFile << "ptr++;\n";
                    } else {
                        cout << "ptr += " << num2 << ";\n";
                        outputFile << "ptr += " << num2 << ";\n";
                    }
                }
                break;

            case '<':
                num = 0;
                num2--;
                if (i < source.size() - 1 && source[i + 1] != '<') {
                    for (int j = 0; j < nest; j++) {
                        cout << "    ";
                        outputFile << "    ";
                    }
                    if (num2 == -1) {
                        cout << "ptr--;\n";
                        outputFile << "ptr--;\n";
                    } else {
                        cout << "ptr -= " << abs(num2) << ";\n";
                        outputFile << "ptr -= " << abs(num2) << ";\n";
                    }
                }
                break;

            case '+':
                num2 = 0;
                num++;
                if (i < source.size() - 1 && source[i + 1] != '+') {
                    for (int j = 0; j < nest; j++) {
                        cout << "    ";
                        outputFile << "    ";
                    }
                    if (num == 1) {
                        cout << "line[ptr]++;\n";
                        outputFile << "line[ptr]++;\n";
                    } else {
                        cout << "line[ptr] += " << num << ";\n";
                        outputFile << "line[ptr] += " << num << ";\n";
                    }
                }
                break;

            case '-':
                num2 = 0;
                num--;
                if (i < source.size() - 1 && source[i + 1] != '-') {
                    for (int j = 0; j < nest; j++) {
                        cout << "    ";
                        outputFile << "    ";
                    }
                    if (abs(num) == 1) {
                        cout << "line[ptr]--;\n";
                        outputFile << "line[ptr]--;\n";
                    } else {
                        cout << "line[ptr] -= " << abs(num) << ";\n";
                        outputFile << "line[ptr] -= " << abs(num) << ";\n";
                    }
                }
                break;

            case '.':
                num2 = 0;
                num = 0;
                for (int j = 0; j < nest; j++) {
                    cout << "    ";
                    outputFile << "    ";
                }
                cout << "cout << line[ptr];\n";
                outputFile << "cout << line[ptr];\n";
                break;

            case ',':
                num2 = 0;
                num = 0;
                for (int j = 0; j < nest; j++) {
                    cout << "    ";
                    outputFile << "    ";
                }
                cout << "cin >> line[ptr];\n";
                outputFile << "cin >> line[ptr];\n";
                break;

            case '[':
                num2 = 0;
                num = 0;
                for (int j = 0; j < nest; j++) {
                    cout << "    ";
                    outputFile << "    ";
                }
                //cout << "for(int i" << nest << " = line[ptr]; i" << nest << " > 0; i" << nest << "--) {\n";
                cout << "while (line[ptr] > 0) {\n";
                outputFile << "while (line[ptr] > 0) {\n";
                nest++;
                break;

            case ']':
                num2 = 0;
                num = 0;
                for (int j = 1; j < nest; j++) {
                    cout << "    ";
                    outputFile << "    ";
                }
                cout << "}\n\n";
                outputFile << "}\n\n";
                nest--;
                break;

            default:
                num = 0;
                num2 = 0;
                break;
        }
    }

    cout << "}";
    outputFile << "}";

    cout << "\n\nTranslated code can be found in the file 'translated.cpp'\n\n";

}

void controller() {
    string source = getInput();
    interpreter(source);
    translator(source);
}