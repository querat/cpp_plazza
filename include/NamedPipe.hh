//
// NamedPipe.hh for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Tue Apr 12 17:53:29 2016 querat_g
// Last update Sun Apr 24 14:11:06 2016 querat_g
//

#ifndef NAMEDPIPE_HH_
# define NAMEDPIPE_HH_

// C
# include <cstdio>
# include <cstring> // strerror

// SysUnix
# include <unistd.h>
# include <fcntl.h>
# include <error.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/select.h>
# include <sys/time.h>
# include <poll.h>

// C++
# include <iostream>
# include <fstream>
# include <sstream>

# include "PlazzaNameSpace.hh"

# define IS_VALID_FD(fd) ((fd != (-1)))

/// Class NamedPipe
/// Permet de transmettre des données entre deux processus
class    NamedPipe
{
public:                // Ctor Dtor

  /// Constructeur de NamedPipe
  /// Construit un objet de type NamedPipe et son fichier fifo
  /// name : chemin du fichier fifo qui sera créé
  NamedPipe(std::string const & name);

  /// Destructeur de NamedPipe
  /// libère les ressources allouées et unlink le fifo du NamedPipe
  ~NamedPipe();

private:               // Attributes
  std::string const     _name;
  char const *          _C_name;

  int                   _fdin;
  int                   _fdout;

private:                // private member functions
  bool                  _close();
  bool                  _tryCreatePipe() const;

public:                 // I/O operations

  /// openWritingEnd()
  /// Ouvre le côté écriture du named pipe
  bool                  openWritingEnd();

  /// openReadingEnd()
  /// Ouvre le côté lecture du named pipe
  bool                  openReadingEnd();

  /// writeTo()
  /// écrit des données dans l'entrée du pipe
  /// data : pointeur sur la mémoire à transmettre
  /// size : taille de la mémoire envoyée dans le pipe
  void                  writeTo(void const *data, size_t size);

  /// readFrom()
  /// lit "size" sur la sortie du pipe et le stocke dans
  /// la mémoire pointée par "buffer"
  bool                  readFrom(void *buffer, size_t size);

public:                 // Boolean operations

  /// isReadyToRead()
  /// Retourne true ou false en fonction de si des données
  /// sont prêtes ou non à être lues
  bool                  isReadyToRead();

};

NamedPipe &             operator<<(NamedPipe &dis, t_FileActionPair const & pair);
NamedPipe &             operator>>(NamedPipe &dis, t_FileActionPair & pair);
NamedPipe &             operator>>(NamedPipe &dis, Plazza::Packet::Raw::Action & act);

#endif // NAMEDPIPE_HH_
