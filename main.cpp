#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <filesystem>


int print_menu() {
	std::cout << "Vocabulary Trainer for German\n";
	std::cout << "Please choose a option: \n";
	std::cout << "(1) Add a new Vocabulary.\n";
	std::cout << "(2) Start Vocabulary test.\n";
	std::cout << "(3) Show Vocabularies\n";
	std::cout << "(4) Exit\n";
	int option = 0;
	std::cout << "Choose a option: ";
	std::cin >> option;
	return option;
}

std::vector<std::string> loadTextFile(std::string textFile) {

	std::ifstream in("./vocabularies/" + textFile);
	std::vector<std::string> newVector;

	std::string str;
	while (std::getline(in, str)) {
		if (str.size() > 0) {
			newVector.push_back(str);
		}
	}
	return newVector;
}

void vectorToTxt(std::string fileName, std::vector<std::string> saveVector) {
	std::filesystem::create_directory("./vocabularies");
	std::ofstream outputFile("./vocabularies/" + fileName);
	std::ostream_iterator<std::string> output_iterator(outputFile, "\n");
	std::copy(saveVector.begin(), saveVector.end(), output_iterator);
}

void ask_word(std::vector<std::string> voc_german, std::vector<std::string> voc_english) {
	int random = rand() % voc_german.size();
	std::string sel_em = voc_german[random];
	std::string sel_translation = voc_english[random];
	std::cout << "Please translate the following word: " << sel_em << "\n";
	std::string userInput;
	std::cin >> userInput;
	if (userInput == sel_translation) {
		std::cout << "Correct!\n";
	}
	else {
		std::cout << "Wrong!\n";
	}
}

void openFile(std::string file) {
	std::fstream out("./vocabularies/" + file);
	if (out.is_open()) {
		std::cout << out.rdbuf();
	}
}

int main() {
	std::vector<std::string> voc_german = loadTextFile("voc_german.txt");
	std::vector<std::string> voc_english = loadTextFile("voc_english.txt");

	int option = print_menu();
	if (option == 1) {
		std::cout << "Please enter the new Vocabulary(German).\n";
		std::string german_word;
		std::string english_word;
		std::cin >> german_word;
		std::cout << "Please enter the Transilation(English).\n";
		std::cin >> english_word;
		// Add German Word and English Word
		voc_german.push_back(german_word);
		voc_english.push_back(english_word);
		std::cout << "Vocabularies added.\n";
		vectorToTxt("voc_german.txt", voc_german);
		vectorToTxt("voc_english.txt", voc_english);
		std::cout << std::to_string(voc_german.size()) << " German Vocabularies\n";
		std::cout << std::to_string(voc_english.size()) << " English Vocabularies\n";
		print_menu();
	}
	else if (option == 2) {
		std::cout << "Vocabulary test starting...\n";
		int i = 0;
		while (i < 10) {
			ask_word(voc_german, voc_english);
			i++;
		}
		print_menu();
	}
	else if (option == 3) {
		std::cout << "\n";
		std::cout << "German Vocabularies:\n";
		openFile("voc_german.txt");
		std::cout << "\n";
		std::cout << "English Vocabularies:\n";
		openFile("voc_english.txt");
		std::cout << "\n";
		print_menu();
	}
	else if (option == 4) {
		return 0;
	}
	else {
		std::cout << "Invalid Input!\n";
		print_menu();
	}
	return 0;
}
