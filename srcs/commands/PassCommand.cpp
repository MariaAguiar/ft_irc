#include "commands/PassCommand.hpp"

PassCommand::PassCommand( UserManager *userManager, ChannelManager *channelManager,
                          std::string args, int fd ) : ACommand( "PASS", userManager, channelManager, args, fd ) {}

PassCommand::~PassCommand() {
}

PassCommand::PassCommand( PassCommand const &src ) : ACommand( src._userManager, src._channelManager ) {
  *this = src;
}

PassCommand &PassCommand::operator=( PassCommand const &src ) {
  if ( this == &src )
    return ( *this );
  ACommand::operator=( src );
  return ( *this );
}

PreparedResponse PassCommand::execute() const {
  if ( _args.length() <= 1 )
    return serverResponse( ERR_NEEDMOREPARAMS, "PASS" );

  std::string str = _args.substr( 1, _args.find_first_of( " \n\r\0", 1 ) - 1 );

  if ( !_userManager->isValidArg( str ) )
    return serverResponse( INVALIDAUTHELEM, "Password" );

  User *user = _userManager->getUser( _userFD );
  if ( user == NULL && str == _userManager->getServerPass() ) {
    user = new User();
    if ( str == _userManager->getServerPass() )
      user->setPassword( true );
    _userManager->addUser( _userFD, user );
    return serverResponse( UPD_AUTHELEM, "Password" );
  }
  else if ( str != _userManager->getServerPass() )
    return serverResponse( ERR_PASSWDMISMATCH, "" );
  else if ( user->getLoggedIn() )
    return serverResponse( ERR_ALREADYREGISTERED, "" );

  PreparedResponse pr;
  std::string resp;
  if ( !user->getPassword() && str == _userManager->getServerPass() ) {
    user->setPassword( true );
    resp = genServerMsg( UPD_AUTHELEM, _userManager->getNick( _userFD ), "Password" );
  }
  if ( _userManager->authenticateUser( _userFD ) ) {
    _userManager->setUserIp( _userFD );
    resp += genServerMsg( RPL_WELCOME, _userManager->getNick( _userFD ), _userManager->getNick( _userFD ) );
  }
  pr.allresponses[resp].push_back( _userFD );
  return pr;
}
