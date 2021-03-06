/*
 *  Copyright (C) 2003 Guilhem Bonnefille <guilhem.bonnefille@free.fr>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Library General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef CONTROLLER_H
#define CONTROLLER_H
 
/**
 * Generic controller for IHM.
 *
 * It defines the 'events' that can occurs.
 */
class Controller
{
 protected:
  Controller(){}
  virtual ~Controller(){}

 public:

  /**
   * A new fetch begin.
   *
   *@param number number of messages to retrieve
   *@param login login used
   *@param server server contacted
   *@param size size to download (in bytes)
   */
  virtual void newFetch(int number,
                        const char *login,
                        const char *server,
                        int size) = 0;

  /**
   * A new message is comming.
   *
   *@param login login used
   *@param server server contacted
   *@param index index of the current message
   *@param number number of messages to retrieve on the current server
   *@param size size (in bytes) of the current message
   */
  virtual void newMessage(const char *login,
                          const char *server,
                          int index,
                          int number,
                          int size) = 0;
  
  /**
   * Previous message completly downloaded.
   */
  virtual void messageFlushed() = 0;
};

#endif /* CONTROLLER_H */
