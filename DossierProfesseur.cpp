#include <string>
#include <fstream>
#include <iostream>
#include "Professeur.cpp"
#include "Etudiant.cpp"
#include "Cours.cpp"


class DossierProfesseur
{
    private:

        // Pointeur vers le debut de la liste chainee des professeurs
        Professeur* tete;

        // Nombre total de professeurs dans la liste chainee
        int nombreProfesseurs = 0;

    public:

        // Construit la structure de la liste chainee en memoire a partir du fichier PF
        DossierProfesseur(char* PF)
        {
            // Au depart la liste = null parce que rien dedans
            tete = nullptr;

            // Lire fichier
            std::ifstream fichierProfesseur(PF);
            if (!fichierProfesseur)
            {
                // Message erreur si fichier != la 
                // cerr = Crier si erreur est present (crier erreur)
                // endl = end line + flush la memoire (end line)
                std::cerr << "Le fichier n'est pas la ou n'existe pas" << std::endl;
                return;
            }

            Professeur* dernierProfesseur = nullptr;
            std::string ligne;

            while (std::getline(fichierProfesseur, ligne))
            {
                if (ligne.empty())
                {
                    continue;
                }

                Professeur* nouveauProf = new Professeur;
                nouveauProf->nom = ligne;  // premiere ligne = nom
                nouveauProf->suivant = nullptr;

                // Lire anciennete
                if (!std::getline(fichierProfesseur, ligne))
                {
                    break;
                }
                nouveauProf->anciennete = std::stoi(ligne);

                // Lire les cours
                nouveauProf->listecours = nullptr;
                Cours* dernierCours = nullptr;

                while (std::getline(fichierProfesseur, ligne) && ligne != "&")
                {
                    Cours* nouveauCours = new Cours;
                    nouveauCours->sigle = ligne;
                    nouveauCours->suivant = nullptr;

                    if (dernierCours == nullptr)
                    {
                        nouveauProf->listecours = nouveauCours; // premier cours
                    }
                    else
                    {
                        dernierCours->suivant = nouveauCours; // relier avec le precedent
                    }

                    dernierCours = nouveauCours; // mettre a jour dernier cours
                }

                // Lire les etudiants
                nouveauProf->listetudiants = nullptr;
                Etudiant* dernierEtudiant = nullptr;

                while (std::getline(fichierProfesseur, ligne) && ligne != "&")
                {
                    Etudiant* nouvelEtudiant = new Etudiant;
                    nouvelEtudiant->nom = ligne;
                    nouvelEtudiant->apres = nullptr;

                    if (dernierEtudiant == nullptr)
                    {
                        nouveauProf->listetudiants = nouvelEtudiant; // premier etudiant
                    }
                    else
                    {
                        dernierEtudiant->apres = nouvelEtudiant; // relier avec le precedent
                    }

                    dernierEtudiant = nouvelEtudiant; // mettre a jour dernier etudiant
                }

                // Ajouter le professeur a la liste chainee
                if (tete == nullptr)
                {
                    tete = nouveauProf; // premier professeur
                    dernierProfesseur = nouveauProf; // mettre a jour dernier professeur
                }
                else
                {
                    dernierProfesseur->suivant = nouveauProf; // relier avec le precedent
                    dernierProfesseur = nouveauProf; // mettre a jour dernier professeur
                }

                nombreProfesseurs++;
            }

            fichierProfesseur.close();
        }

        // Detruit la liste chainee existant en memoire pour eviter les fuites de memoire
        // Regarder tout la liste si pas vide while != null et supprimer si != null
        // Important de sauvegarder le pointeur vers le suivant pour continuer ensuite la supression
        ~DossierProfesseur()
        {
            // Pointeur va sur le premier professeur de la liste = tete de la liste
            Professeur* professeurActuel = tete;

            // Until le pointeur professeur n'est pas null on continue les operations
            while (professeurActuel != nullptr)
            {
                // Structure* suivantObject = Pointeur de l'object actuel -> va vers le suivant
                Professeur* suivantProfesseur = professeurActuel->suivant;

                Cours* coursActuel = professeurActuel->listecours;

                // Until le pointeur cours n'est pas null on continue les operations
                while (coursActuel != nullptr)
                {
                    Cours* suivantCours = coursActuel->suivant;

                    delete coursActuel;

                    coursActuel = suivantCours;
                }

                Etudiant* etudiantActuel = professeurActuel->listetudiants;

                // Until le pointeur etudiant n'est pas null on continue les operations
                while (etudiantActuel != nullptr)
                {
                    Etudiant* suivantEtudiant = etudiantActuel->apres;

                    delete etudiantActuel;

                    etudiantActuel = suivantEtudiant;
                }

                delete professeurActuel;

                professeurActuel = suivantProfesseur;
            }

            // On remet tete = null pour avoir un pointeur vide qui ne prend pas d'espace
            tete = nullptr;
        }

        // Supprime de la liste chainee tous les professeurs dont le nom est "name"
        // Regarder la liste chaine avec pointeur, si nom != name on continue, else supprime 
        void supprimer(char* name)
        {
            // TODO
        }

        // Retourne le nom du premier professeur ayant le plus d'etudiants
        // Regarder la liste chaine avec pointeur, si nom != name on continue, else supprime 
        char* afficher_leprofplusetudiant() const
        {
            // TODO
            return nullptr;
        }

        // Retourne le cours le plus demande dans la liste.
        // En cas d'egalite, choisit celui du (premier) professeur le moins ancien.
        // Regarder la liste chaine avec pointeur, count le cours le plus demande (addition)
        char* affichercoursplusdemande() const
        {
            // TODO
            return nullptr;
        }

        // Affiche le nombre de professeurs souhaitant enseigner le cours "coursdonne"
        int affichernbreprofpouruncours(std::string* coursdonne) const
        {
            // TODO
            return 0;
        }

        // Creer un nouveau fichier nomme PF{2}, PF{3}... PF{n}
        // Recopie la liste chainee mise a jour dans le nouveau fichier PF
        void recopier(char* PF)
        {
            // Creer le nouveau fichier
            static int compteur = 1; // utilisation d'une variable statique pour garder la valeur entre les appels
            compteur++;

            // Utiliser .c_str() parce que ont travail avec const char* et ofstream donc on veut convertir 
            std::string nouveauFichier = std::string(PF) + "{" + std::to_string(compteur) + "}";

            // Ouvrir fichier
            std::ofstream fichierSortie(nouveauFichier.c_str());

            if (!fichierSortie)
            {
                std::cerr << "Erreur lors de l'ouverture du fichier" << std::endl;
                return;
            }

            Professeur* professeurActuel = tete;

            while (professeurActuel != nullptr)
            {
                fichierSortie << professeurActuel->nom << std::endl;
                fichierSortie << professeurActuel->anciennete << std::endl;

                // Parcourir la liste des cours et ecrire chaque cours suivi d'un saut de ligne
                Cours* coursActuel = professeurActuel->listecours;

                while (coursActuel != nullptr)
                {
                    fichierSortie << coursActuel->nom << std::endl;
                    coursActuel = coursActuel->suivant;
                }

                // Marqueur de fin de la liste  
                fichierSortie << "&" << std::endl;

                // Parcourir la liste des etudiants et ecrire chaque etudiant suivi d'un saut de ligne
                Etudiant* etudiantActuel = professeurActuel->listetudiants;

                while (etudiantActuel != nullptr)
                {
                    fichierSortie << etudiantActuel->nom << std::endl;
                    etudiantActuel = etudiantActuel->apres;
                }

                // Marqueur de fin de la liste 
                fichierSortie << "&" << std::endl;

                // Passer au professeur suivant
                professeurActuel = professeurActuel->suivant;
            }

            // Fermer le fichier 
            fichierSortie.close();

            std::cout << "Liste chainee copiee dans : " << nouveauFichier << std::endl;
        }
};
