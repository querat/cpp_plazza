//
// dataCollector.hh for  in /home/schmou/cpp/cpp_plazza/include
// 
// Made by schmou_a
// Login   <schmou@epitech.net>
// 
// Started on  Mon Apr 18 14:00:21 2016 schmou_a
// Last update Fri Apr 22 16:28:20 2016 schmou_a
//

#ifndef DATACOLLECTOR_HH_
# define DATACOLLECTOR_HH_

#include "../querat_g/include/PlazzaNameSpace.hh"
#include <string>
#include <regex>

class dataCollector
{

public:

  /// Constructeur DataCollector
  /// Construit un objet de type DataCollector
  /// file_info : paire contenant le chemin du fichier et le type de données à extraire
  /// reg : regex à injecter dans le fichier
  dataCollector(t_FileActionPair &file_info, std::regex reg);

  /// Destructeur Datacollector
  /// Detruit un objet de type Datacollector
  ~dataCollector();

  /// Extracteur de données
  /// Récupère les données contenue dans le fichier et effectue un bruteforce si nécessaire
  std::string	extract_data();

  /// Déchiffrement César
  /// Déchiffe le fichier donné avec la clé donnée
  /// to_uncipher : contenu du fichier à déchiffrer
  /// key : clé de déchiffrement
  std::string	caesarUnCipher(const std::string &to_uncipher, const unsigned short key);

  /// Déchiffrement Xor
  /// Déchiffe le fichier donné avec la clé donnée
  /// to_uncipher : contenu du fichier à déchiffrer
  /// key : clé de déchiffrement
  std::string	xorUnCipher(const std::string &to_uncipher, const unsigned short key);

  /// Bruteforce  César
  /// Déchiffe le fichier donné avec l'ensemble des clés possibles en suivant le code César
  /// to_uncipher : contenu du fichier à déchiffrer
  std::string	caesarBruteForce(const std::string &to_uncipher);

  /// Bruteforce  Xor
  /// Déchiffe le fichier donné avec l'ensemble des clés possibles avec un Xor
  /// to_uncipher : contenu du fichier à déchiffrer
  std::string	xorBruteForce(const std::string &to_uncipher);

private:

    bool		heuristicsXor(const std::string &to_uncipher, const unsigned short key);
    bool		heuristicsCaesar(const std::string &to_uncipher, const unsigned short key);
  int		my_isprint(char c);
  std::string  	_raw_data;
  std::string  	_processed_data;
  std::regex	_reg;
  Plazza::Action::Type _to_get;
};

#endif
