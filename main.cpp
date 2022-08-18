#include <iostream>
#include <fstream>
#include <string>
#include <condition_variable>
#include <atomic>
#include "nnue_training_data_stream.h"
using namespace std;
int main (int argc, char *argv[]) {
    if (argc != 4) {
        cout << "Usage: <input_file> <max_fens> <skip_fens>" << endl;
        return 1;
    }
    const int MAX = stoi(argv[2]), SKIP = stoi(argv[3]);
    auto reader = binpack::CompressedTrainingDataEntryReader(argv[1]);
    ofstream fens("fens.txt"), scores("scores.txt");

    binpack::TrainingDataEntry entry;
    for (int i = 0; i < SKIP; i++) {
        if (reader.hasNext()) {
            entry = reader.next();
        } else {
            fens.close();
            scores.close();
            return 1;
        }
    }
    for (int i = 0; i < MAX; i++) {
        if (reader.hasNext()) {
            entry = reader.next();
            fens << entry.pos.fen() << endl;
            scores << entry.score << endl;
        } else {
            fens.close();
            scores.close();
            return 2;
        }
    }
    fens.close();
    scores.close();
    return 0;
}
