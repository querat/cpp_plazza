//
// Plazza.cpp for  in /home/querat_g/tmp/cpp_plazza/querat_g/src
//
// Made by querat_g
// Login   <querat_g@epitech.net>
//
// Started on  Sun Apr 17 16:11:56 2016 querat_g
// Last update Fri Apr 22 17:11:11 2016 querat_g
//

#include "PlazzaNameSpace.hh"
#include "Plazza.hh"
#include "SubMain.hh"

static Plazza::Main     *g_plazza = nullptr;

void            sigHandler(int sig) {
  (void)sig;
  if (g_plazza) {
    DEBUG("^C caught");
    g_plazza->setForcedExitState();
  }
}

Plazza::Main::Main(std::string nbThreads)
  : _nbThreads(1)
  , _stdinIsClosed(false)
  , _forcedExit(false)
{
  std::regex    isNum("^\\-?[0-9]+$");

  if (!std::regex_match(nbThreads, isNum))
    throw (std::invalid_argument(ERR_NOTANUMBER));

  this->_nbThreads = std::atoi(nbThreads.c_str());
  if (this->_nbThreads <= 0)
    throw (std::invalid_argument(ERR_INVALIDNUM));

  g_plazza = this;
  signal(SIGINT, sigHandler);
  signal(SIGTERM, sigHandler);
}

Plazza::Main::~Main(){}

bool
Plazza::Main::_forkPlazza()
{
  pid_t         pid = -1;
  pid = fork();
  if (pid == -1)
    {
      std::cerr << "fork failed ! " << std::endl;
      return (false);
    }

  pid_t         tmpPid = pid ? pid : getpid();
  NamedPipe     *pipe1 = new NamedPipe(Plazza::makeFifoNameFromPid(tmpPid, true));
  NamedPipe     *pipe2 = new NamedPipe(Plazza::makeFifoNameFromPid(tmpPid, false));

  if (pid) { // parent
    this->_childs.insert(std::make_pair(pid, ChildProcess(pid, pipe1, pipe2, _nbThreads)));
  }
  else { // child
    SubMain   *subProcess = new SubMain(getpid(), pipe1, pipe2);
    subProcess->mainLoop();
    delete (subProcess);
    _Exit(0);
  }

  return (true);
}

void
Plazza::Main::setForcedExitState() {
  _forcedExit = true;
}

void
Plazza::Main::printActionsQueue() const {
  t_ActionDeque::const_iterator it = _actionQueue.begin();

  CERR("now printing actions to std::cerr ----------");
  while (it != _actionQueue.end()) {
    CERR(it->first << " :: " << it->second);
    ++it;
  }
  CERR("! print ------------------------------------");
}

void
Plazza::Main::killProcesses()
{
  t_ChildrenMapIt       it = _childs.begin();

  while (it != _childs.end()) {
    DEBUG("killing child " << it->first);
    if ((kill(it->first, SIGKILL)) == -1) {
      CERR(RED "Kill failed " << it->first << " : " << strerror(errno) <<  WHITE);
    }
    waitpid(it->first, nullptr, WNOHANG);
    it = _childs.erase(it);
  }
}

bool
Plazza::Main::_shouldExit() const
{
  if ((!this->isBusy() && this->_stdinIsClosed) ||
      (this->_forcedExit))
    return (true);
  return (false);
}

void
Plazza::Main::_readStdin() {
  std::getline(std::cin, _stdinString);
}

bool
Plazza::Main::isBusy() const {
  t_ChildrenMap::const_iterator it = _childs.begin();

  while (it != _childs.end()) {
    if (it->second.isBusy())
      return (true);
    ++it;
  }

  return (false);
}

t_ChildrenMapIt
Plazza::Main::_firstAvailableProcess() {
  t_ChildrenMapIt       it = _childs.begin();

  while (it != _childs.end()) {
    if (!it->second.reachedMaxCharge() && it->second.isAlive()) {
      return (it);
    }
    ++it;
  }
  return (it);
}

void
Plazza::Main::_pollAndGetAnswers() {
  t_ChildrenMapIt it = _childs.begin();

  while (it != _childs.end()) {
    if (it->second.hasAnswerReady()) {
      DEBUG("pollAndGetAnswers OK");
      it->second.receiveAnswer(_answers);
    }
    ++it;
  }
}

void
Plazza::Main::_dumpAnswers() {

  if (_answers.empty()){
    return ;
  }

  COUT("ANSWER " << _answers.front() << " !ANSWER");

  _answers.pop_front();
}

void
Plazza::Main::_cleanDeadChildren() { // #Auschwitz
  t_ChildrenMapIt       it = _childs.begin();

  if (_childs.empty())
    return ;

  while (it != _childs.end()) {
    if (!(it->second.isAlive())) {
      DEBUG(RED "child " << it->second.getPid() << "died" WHITE);
      it = _childs.erase(it);
    }
    else
      ++it;
  }
}

int
Plazza::Main::mainLoop()
{
  Parser        cmd;

  CERR("Welcome ! enter a command plz.");

  while (!this->_shouldExit())
    {
      // Call uncle adolf
      this->_cleanDeadChildren();

      // Poll, read STDIN and parse its content into actions
      if ((!std::cin.eof()) && pollFd(STDIN_FILENO)) {
        DEBUG("Plazza::Main reading from stdin");
        _readStdin();
        cmd.parse(this->_stdinString, this->_actionQueue);
      }

      // ^D detection
      if (std::cin.eof() && !_stdinIsClosed) {
        _stdinIsClosed = true;
        CERR(YELLOW "Stdin Closed, now waiting for completion of commands ..." WHITE);
      }

      // Dispatch and send eventual commands to children
      if (!_actionQueue.empty()) {

        // get the first process with available task space
        t_ChildrenMapIt it;
        if ((it = this->_firstAvailableProcess()) != _childs.end()) {
          DEBUG("Available process found : " << it->second.getPid());

          it->second.sendAction(_actionQueue.front());
          _actionQueue.pop_front();
        }

        else { // or fork the process
          DEBUG(CYAN "No available process found : forking ..." WHITE);
          _forkPlazza();
          DEBUG("... Done !");
        } // !if (!_actionQueue.empty())

      }

      // get and dump the answers from the subProcesses
      _pollAndGetAnswers();
      _dumpAnswers();
    }

  return (0);
}
