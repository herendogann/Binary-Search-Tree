#include <iostream>
#include "takeInput.h"
#include "PrimaryTree.h"
#include "SecondaryTree.h"

using namespace std;

int main(int argc, char **argv) {
    // creating commands array
    int size = inputSize(argv[1]);
    string *commands = inputArray(argv[1]);

    // opening output files
    ofstream output(argv[2], ios::out);
    ofstream output2(argv[3], ios::out);

    // checking if output files has opened
    if (output.is_open() && output2.is_open()) {
        // creating a primary tree
        PrimaryTree primaryTree;

        // traversing in commands array to take commands in given order in input
        for (int i = 0; i < size; ++i) {
            if (commands[i] == "insert") {
                primaryTree.insert(commands[i + 1]);
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                primaryNode->secondaryTree.insert(commands[i + 1], commands[i + 2], stoi(commands[i + 3]));
                primaryNode->secondaryTree2.insert(commands[i + 1], commands[i + 2], stoi(commands[i + 3]));
            }
            if (commands[i] == "remove") {
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                primaryNode->secondaryTree.remove(commands[i + 2]);
                primaryNode->secondaryTree2.remove(commands[i + 2]);
            }
            if (commands[i] == "printItem") {
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                if (primaryNode != nullptr) {
                    SecondaryNode *secondaryNode = primaryNode->secondaryTree.search(commands[i + 2]);
                    SecondaryNode2 *secondaryNode2 = primaryNode->secondaryTree2.search(commands[i + 2]);
                    if (secondaryNode != nullptr) {
                        output << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{\n\"" <<
                               secondaryNode->category << "\":\n\t\"" << secondaryNode->name << "\":\""
                               << secondaryNode->price << "\"\n}\n";
                    } else {
                        output << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    }
                    if (secondaryNode2 != nullptr) {
                        output2 << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{\n\"" <<
                                secondaryNode2->category << "\":\n\t\"" << secondaryNode2->name << "\":\""
                                << secondaryNode2->price << "\"\n}\n";
                    } else {
                        output2 << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    }
                } else {
                    output << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    output2 << "command:printItem\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                }
            }
            if (commands[i] == "printAllItemsInCategory") {
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                if (primaryNode->secondaryTree.isEmpty()) {
                    output << "command:printAllItemsInCategory\t" << commands[i + 1] << "\n{\n\"" << primaryNode->name
                         << "\":{}\n}\n";
                } else {
                    output << "command:printAllItemsInCategory\t" << commands[i + 1] << "\n{\n\"" << primaryNode->name
                         << "\":\n";
                    primaryNode->secondaryTree.printLevelByLevel(&output);
                    output << "}\n";
                }
                if (primaryNode->secondaryTree2.isEmpty()) {
                    output2 << "command:printAllItemsInCategory\t" << commands[i + 1] << "\n{\n\"" << primaryNode->name
                           << "\":{}\n}\n";
                } else {
                    output2 << "command:printAllItemsInCategory\t" << commands[i + 1] << "\n{\n\"" << primaryNode->name
                           << "\":\n";
                    primaryNode->secondaryTree2.printLevelByLevel(&output2);
                    output2 << "}\n";
                }
            }
            if (commands[i] == "printAllItems") {
                if (primaryTree.isEmpty()) {
                    output << "command:printAllItems\n{}\n";
                    output2 << "command:printAllItems\n{}\n";
                } else {
                    output << "command:printAllItems\n{\n";
                    primaryTree.printLevelByLevel1(&output);
                    output << "}\n";

                    output2 << "command:printAllItems\n{\n";
                    primaryTree.printLevelByLevel2(&output2);
                    output2 << "}\n";
                }

            }
            if (commands[i] == "find") {
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                if (primaryNode != nullptr) {
                    SecondaryNode *secondaryNode = primaryNode->secondaryTree.search(commands[i + 2]);
                    SecondaryNode2 *secondaryNode2 = primaryNode->secondaryTree2.search(commands[i + 2]);

                    if (secondaryNode != nullptr) {
                        output << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{\n\"" <<
                               secondaryNode->category << "\":\n\t\"" << secondaryNode->name << "\":\""
                               << secondaryNode->price << "\"\n}\n";
                    } else {
                        output << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    }

                    if (secondaryNode2 != nullptr) {
                        output2 << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{\n\"" <<
                                secondaryNode2->category << "\":\n\t\"" << secondaryNode2->name << "\":\""
                                << secondaryNode2->price << "\"\n}\n";
                    } else {
                        output2 << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    }
                } else {
                    output << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                    output2 << "command:find\t" << commands[i + 1] << "\t" << commands[i + 2] << "\n{}\n";
                }
            }
            if (commands[i] == "updateData") {
                PrimaryNode *primaryNode = primaryTree.search(commands[i + 1]);
                SecondaryNode *secondaryNode = primaryNode->secondaryTree.search(commands[i + 2]);
                SecondaryNode2 *secondaryNode2 = primaryNode->secondaryTree2.search(commands[i + 2]);
                secondaryNode->updatePrice(stoi(commands[i + 3]));
                secondaryNode2->updatePrice(stoi(commands[i + 3]));
            }
        }
    }
    else {
        cout << "There is a problem with opening output files." << endl;
    }

    // closing output files
    output.close();
    output2.close();

    // deleting commands array
    delete[] commands;
}
