/**
 * Demo for Family Tree
 * 
 * First version by Adam Lev-Ari,  2019-12
 * Second version by Erel Segal-Halevi, 2020-04
 */

#include <iostream>
using namespace std;

#include "FamilyTree.hpp"

int main() {
	family::Tree T("Yosef"); // Yosef is the "root" of the tree (the youngest person).
	T.addFather("Yosef", "Yaakov") // Tells the tree that the father of Yosef is Yaakov.
	 .addMother("Yosef", "Rachel") // Tells the tree that the mother of Yosef is Rachel.
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Isaac", "Avraham")
	 .addFather("Avraham", "Terah");
	
	T.display(); // Displays the tree in a human-friendly format.

	cout << T.relation("Yaakov") << endl; // Prints "father"
	cout << T.relation("Rachel") << endl; // Prints "mother"
	cout << T.relation("Rivka") << endl; // Prints "grandmother"
	cout << T.relation("Avraham") << endl; // Prints "great-grandfather"
	cout << T.relation("Terah") << endl; // Prints "great-great-grandfather"
	cout << T.relation("xyz") << endl; // Prints "unrelated"
	cout << T.relation("Yosef") << endl; // Prints "me"

	cout << T.find("mother") << endl; // Prints "Rachel"
	cout << T.find("great-great-grandfather") << endl; // Prints "Avraham"
	try {
		cout << T.find("uncle") << endl; // Throws an exception
	} catch (const exception& ex) {
	 	cout << ex.what() << endl; // Prints "The tree cannot handle the 'uncle' relation"
	}

	T.remove("Avraham"); // Removes Avraham and Terah
	cout << T.relation("Terah") << endl; // Prints "unrelated"
    return 0;
}