#!/bin/sh
#  Copyright (C) 2003 Guilhem Bonnefille <guilhem.bonnefille@free.fr>
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Library General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

if [ -z "$TXTFETCHMAILMON" ]
then
  TXTFETCHMAILMON="txtfetchmailmon"
fi
if [ ! -x "$TXTFETCHMAILMON" ]
then
  echo "Error: '$TXTFETCHMAILMON' is not executable." >&2
  exit 1
fi

INFO=number
case $1 in
  -size) INFO=size ;;
  -number) INFO=number ;;
esac

previous_email=""

$TXTFETCHMAILMON |\
  sed 's/^\(.*\): .*(\([0-9]*\)%), \([0-9]*\)%.*$/\1 \2 \3/' |\
  while read email number size
  do
    if [ "$previous_email" != "$email" ]
    then
      echo "XXX"
      echo "$email"
      echo "XXX"
    fi
    eval echo \$$INFO
  done | dialog --begin 0 0 --gauge test 10 70
