#!/bin/bash
if [ `find /lib -name "libGL.so"` ]
then
  echo "Libreria  de  OpenGL  en  /lib"
elif [ `find /usr/lib -name "libGL.so" | grep head -1` ]
then
  echo "Libreria de OpenGL en /usr/lib"
elif [ `find /usr/local/lib -name "libGL.so"` ]
then
  echo "Libreria de OpenGL en /usr/local/lib"
else
  echo "No se encontro la libreria de OpenGL"
fi
