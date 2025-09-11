/*

*/
#include<string>
#include "Etudiant.cpp"
#include "Professeur.cpp"


struct Cours 
{
	std::string sigle;
	Cours* suivant;
};