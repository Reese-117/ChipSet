#include <iostream>
#include <string>
using namespace std;

class Chip {
private:
    char chipType;  // Type of Chip (Add, Subtraction, Multiplication, Negation, Output, and Input)
    string id;      // Unique ID for chip (e.g., "I1", "A100")
    Chip* input1;   // First input chip pointer
    Chip* input2;   // Second input chip pointer
    Chip* output;   // Output chip pointer
    double inputValue; // Input value for input chip
    double outputValue; // Output value for output chip

public:
    Chip(char type, const string& id);   // Constructor with type and ID
    void setInput1(Chip* inputChip);     // Setting first input chip (can be null)
    void setInput2(Chip* inputChip);     // Setting second input chip (can be null)
    Chip* getInput1() const;             // Getter for input1
    void setOutput(Chip* outputChip);    // Setting the output chip
    void setInputValue(double inputValue);  // Set the input value for an input chip
    double compute();                    // Method to compute values based on chip type
    void Display();                      // Displays the chip's information and connections
    string getID() const;                // Getter for chip ID
    Chip* getOutput() const;         // Getter for output chip
    ~Chip();                             // Destructor
};

// Constructor
Chip::Chip(char type, const string& IDnum) {
    chipType = type;// Set chip type
    this->id = type + IDnum;  // Combine type and number into ID (e.g., "A100", "I1")
    input1 = nullptr; // Initialize input1 to nullptr
    input2 = nullptr; // Initialize input2 to nullptr
    output = nullptr;// Initialize output to nullptr
    inputValue = 0;// Initialize input value to 0
}

// Setters
void Chip::setInput1(Chip* inputChip) {
    input1 = inputChip;
}

void Chip::setInput2(Chip* inputChip) {
    input2 = inputChip;
}

void Chip::setOutput(Chip* outputChip) {
    output = outputChip;
}

void Chip::setInputValue(double value) {
    inputValue = value;
}

// Getters
string Chip::getID() const {
    return id;  // Return full ID (e.g., "I1", "A100")
}

Chip* Chip::getOutput() const {
    return output;
}

Chip* Chip::getInput1() const {
    return input1;
}

// Compute logic based on chip type
double Chip::compute() {
    switch (chipType) {
        case 'I':  // Input chip
            
            return inputValue;

        case 'A':  // Add chip
            if (input1 != nullptr && input2 != nullptr) {
                double val1 = input1->compute();
                double val2 = input2->compute();
                outputValue = val1 + val2;
                
            } 
            break;

        case 'S':  // Subtract chip
            if (input1 != nullptr && input2 != nullptr) {
                double val1 = input1->compute();
                double val2 = input2->compute();
                outputValue = val1 - val2;
                
            } 
            break;

        case 'M':  // Multiply chip
            if (input1 != nullptr && input2 != nullptr) {
                double val1 = input1->compute();
                double val2 = input2->compute();
                outputValue = val1 * val2;
            } 
            break;

        case 'D':  // Divide chip
            if (input1 != nullptr && input2 != nullptr) {
                double val1 = input1->compute();
                double val2 = input2->compute();
                if (val2 != 0) {
                    outputValue = val1 / val2;
                } else {
                    
                    outputValue = 0;  // Set output to 0 or handle as appropriate
                }
            } 
            break;

        case 'N':  // Negate chip
            if (input1 != nullptr) {
                outputValue = -input1->compute();
                
            } 
                
            
            break;

        case 'O':  // Output chip
            if (input1 != nullptr) {
                outputValue = input1->compute();
                
            }
            return outputValue;

        default:
            
            return 0;
    }

    return outputValue;
}


// Display chip connections and output in the correct format
void Chip::Display() {
    if (chipType == 'I') {
        if (output != nullptr) {
            cout << id << ", Output = " << output->getID() << endl;
        }
    } else {
        if (input1 != nullptr && input2 != nullptr) {// Check if both inputs are connected
            cout << id << ", Input 1 = " << input1->getID() << ", Input 2 = " << input2->getID();
        } else if (chipType == 'N') {
            if (input1 != nullptr) {
                cout << id << ", Input 1 = " << input1->getID() << ", Input 2 = None";
            }
        } else if (input1 != nullptr) {// Check if only input1 is connected
            cout << id << ", Input 1 = " << input1->getID();
        }

        if (output != nullptr) {// Check if output is connected
            cout << ", Output = " << output->getID();
        }
        cout << endl;
    }
}

// Destructor (no need to delete input/output chips since they are externally managed)
Chip::~Chip() {}

int main() {
    int numChips, numCommands;
    Chip** allChips;

    // Read number of chips
    cin >> numChips;

    // Create an array of Chip object pointers
    allChips = new Chip*[numChips];

    // Read chip IDs and types
    for (int i = 0; i < numChips; i++) {
        char chipType;
        string chipNumber;
        cin >> chipType >> chipNumber;
        allChips[i] = new Chip(chipType, chipNumber);  // Create chip with type and number
    }

    // Read number of commands
    cin >> numCommands;

    // Process each command
    for (int i = 0; i < numCommands; i++) {
        char commandType;
        string id1, id2;
        double value;

        cin >> commandType;

        if (commandType == 'A') {
            // Connect two chips: id1 -> id2
            cin >> id1 >> id2;
            Chip* chip1 = nullptr;
            Chip* chip2 = nullptr;

            // Find the chips by ID
            for (int j = 0; j < numChips; j++) {
                if (allChips[j]->getID() == id1) {
                    chip1 = allChips[j];
                }
                if (allChips[j]->getID() == id2) {
                    chip2 = allChips[j];
                }
            }

            if (chip1 != nullptr && chip2 != nullptr) {
                // Assign input to the chip
                if (chip2->getInput1() == nullptr) {
                    chip2->setInput1(chip1);
                } else {
                    chip2->setInput2(chip1);
                }
                chip1->setOutput(chip2);
            }
//LLM Notes: I used LLM to help me understand how to connect the chips
        } else if (commandType == 'I') {
            // Set input value: id1 = value
            cin >> id1 >> value;
            for (int j = 0; j < numChips; j++) {
                if (allChips[j]->getID() == id1) {
                    allChips[j]->setInputValue(value);
                }
            }

        } else if (commandType == 'O') {
            // Output the result of a chip
            cin >> id1;
            Chip* outputChip = nullptr;

            for (int j = 0; j < numChips; j++) {
                if (allChips[j]->getID() == id1) {
                    double result = allChips[j]->compute();  // Compute the final output
                    outputChip = allChips[j];  // Store the output chip for later display
                    cout << "Computation Starts" << endl;
                    cout << "The output value from this circuit is " << result << endl;
                    cout << "***** Showing the connections that were established" << endl;
                }
            }

            // Display all chips except the output chip
            for (int k = 0; k < numChips; k++) {
                if (allChips[k]->getID() != id1) {
                    allChips[k]->Display();
                }
            }

            // Display the output chip last
            if (outputChip != nullptr) {
                outputChip->Display();
            }
        }
    }


    // Clean up dynamically allocated memory
    for (int i = 0; i < numChips; i++) {
        delete allChips[i];
    }
    delete[] allChips;

    return 0;
};


