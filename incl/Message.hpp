#pragma once
#ifndef __MESSAGE_HPP__
#define __MESSAGE_HPP__

#include <sstream>
#include <string>

#include "User.hpp"

struct UnparsedMsg {
  std::string message;
  bool        internal;
  bool        unfinished;
};

struct ParsedMsg {
  std::string commandName;
  std::string args;
  bool        internal;
};

// Dunno if we need them
#define ERR_CANNOTSENDTOCHAN 404  // Use when: user sends a message to a channel for which he is only invited
#define ERR_UNKNOWNCOMMAND 421    // Use when: receiving an unknown command
#define ERR_KEYSET 467            // Use when: setting a channel key when channel already has a key
#define ERR_CANTKILLSERVER 483    // Use when: received A KILL command
#define ERR_USERSDONTMATCH 502    // Use when: user tries to change the userinfo of another user

// General Purpose
#define ERR_NOSUCHNICK 401       // Use when: nickname given to command doesn't exist
#define ERR_TOOMANYTARGETS 407   // Use when: too many recipients are given to a command
#define ERR_NORECIPIENT 411      // Use when: no recipient is given to a command that expects it
#define ERR_NONICKNAMEGIVEN 431  // Use when: no nickname is given to a command that expects it
#define ERR_NOTREGISTERED 451    // Use when: getting a command not usable by an unauthenticated user
#define ERR_NEEDMOREPARAMS 461   // Use when: received command lacks parameters

// Channel
#define RPL_CHANNELMODEIS 324     // Use when: viewing channel modes
#define RPL_NAMREPLY 353          // Use when: notifying the channel about a user's status or nickname change
#define ERR_NOSUCHCHANNEL 403     // Use when: received channel name doesn't exist
#define ERR_USERNOTINCHANNEL 441  // Use when: a user sends a message to a channel he is not a member of
#define ERR_USERONCHANNEL 443     // Use when: inviting a user to a channel he is already on
#define ERR_INVITEONLYCHAN 473    // Use when: user tries to join invite only channel
#define ERR_BADCHANNELKEY 475     // Use when: user tries to join a key-needed-channel with an invalid key or no key
#define ERR_CHANOPRIVSNEEDED 482  // Use when: regular user tries to use a command only allowed to channel operators
#define ERR_CHANNELISFULL 471     // Use when: channel has a max user limit and can't receive a new user

// Authentication
#define RPL_WELCOME 1  // Use when: login is successful

// PASS Cmd
#define ERR_PASSWDMISMATCH 464  // Use when: getting the server password wrong

// USER cmd
#define ERR_ALREADYREGISTERED 462  // Use when: received USER command by an already authenticated user

// NICK Cmd
#define ERR_ERRONEUSNICKNAME 432  // Use when: nickname to (re)place is invalid
#define ERR_NICKNAMEINUSE 433     // Use when: nickname to (re)place is already taken

// TOPIC Cmd
#define RPL_NOTOPIC 331  // Use when: viewing channel topic when topic is empty
#define RPL_TOPIC 332    // Use when: topic change / addition is successful

// MODE Cmd
#define ERR_UNKNOWNMODE 472  // Use when: MODE has an unknown mode flag

// PRIVMSG Cmd
#define ERR_NOTEXTTOSEND 412  // Use when: the PRIVMSG has no message

// Custom Msgs
#define UPD_AUTHELEM 601            // Use when: successfully updated an authentication element
#define INVALIDAUTHELEM 602         // Use when: new authentication element has invalid characters
#define ERR_USERNAMEINUSE 603       // Use when: username to (re)place is already taken
#define ERR_USERNOTFOUND 604        // Use when: username is different than necessary in file transfer
#define ERR_IPNOTFOUND 605          // Use when: user ip is different than necessary in file transfer
#define ERR_TARGETNOTAUTH 606       // Use when: target of a command is not autheticated
#define ERR_TARGETNOTINCHANNEL 607  // Use when: target of a command not in channel
#define ERR_TARGETALREADYINV 608    // Use when: target of a command INVITE already invited
#define ERR_TARGETNOTOPER 609       // Use when: target of a command not in channel
#define ERR_TARGETISOPER 610        // Use when: target of MODE +o is already operator

std::string genServerMsg( int code, std::string nick, std::string param );
std::string genUserMsg( User *userinfo, std::string msg );

#endif
