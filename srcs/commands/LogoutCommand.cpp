#include "commands/LogoutCommand.hpp"

LogoutCommand::LogoutCommand( UserManager *userManager, ChannelManager *channelManager,
                              std::string args, int fd ) : ACommand( "LOGOUT", userManager, channelManager, args, fd ) {}

LogoutCommand::~LogoutCommand() {
}

LogoutCommand::LogoutCommand( LogoutCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

LogoutCommand &LogoutCommand::operator=( LogoutCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse LogoutCommand::execute() const {
  std::map<std::string, Channel *> channels = _channelManager->getAllChannels();
  for ( std::map<std::string, Channel *>::iterator it = channels.begin(); it != channels.end(); it++ ) {
    it->second->removeUser( _userFD );
    it->second->removeOperator( _userFD );
  }
  _userManager->releaseUserInfo( _userFD );
  return PreparedResponse();
}
