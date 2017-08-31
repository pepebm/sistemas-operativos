#!bin/bash

whoami > quien
cat quien
a="usuario"
echo $a
cat quien | while read LINE
do
  if [ $quien != "root" ]
  then
    echo "Debes ser root para poder correr el script (no se puede con sudo)"
    exit 1
  fi
done
rm quien

echo "listo para instalar"

apt-get install -y libreoffice
apt-get install -y g++
apt-get install -y cmake
apt-get install -y cmake-curses-gui
apt-get install -y k3b
apt-get install -y xfce4-xkb-plugin
apt-get install -y octave
apt-get install -y scilab
apt-get install -y scilab-plotlib

echo "Instalando chrome"
apt-get install -y libcurl3
wget --no-check-certificate https://dl.google.com/linux/direct/google-chrome-stable_current_amd64.deb
dpkg -i google-chrome-stable_current_amd64.deb
rm google-chrome-stable_current_amd64.deb

echo "Removiendo programas inseguros"
apt-get remove -y ftp
dpkg -r telnet
dpkg -P telnet
dpkg -r samba-common smbclient samba-common-bin
dpkg -P samba-common
dpkg -r transmission-gtk
dpkg -r transmission-common
dpkg -P transmission-gtk
dpkg -r pptp-linux network-manager-pptp network-manager-pptp-gnome
dpkg -P pptp-linux network-manager-pptp
dpkg -r ppp pppoeconf pppconfig
dpkg -P ppp pppoeconf pppconfig
dpkg -r rsync
dpkg -P rsync
dpkg -r vinagre
dpkg -P vinagre
dpkg -r xchat xchat-common xchat-indicator
dpkg -P xchat

echo "Se verifica la existencia de algunos paquetes."

dpkg -l | grep -i mail
dpkg -l | grep -i evolution
dpkg -l | grep -i ftp
dpkg -l | grep -i talk
dpkg -l | grep -i finger
dpkg -l | grep -i telnet
dpkg -l | grep -i samba
dpkg -l | grep -i smb
dpkg -l | grep -i transmission
dpkg -l | grep -i torrent
dpkg -l | grep -i msn
dpkg -l | grep -i pidgin
dpkg -l | grep -i pptp
dpkg -l | grep -i ppp
dpkg -l | grep -i openconnect
dpkg -l | grep -i vpn
dpkg -l | grep -i rsh
dpkg -l | grep -i rlogin
dpkg -l | grep -i rtp
dpkg -l | grep -i rdate
dpkg -l | grep -i rsync
dpkg -l | grep -i vino
dpkg -l | grep -i vinagre
dpkg -l | grep -i nfs
dpkg -l | grep -i ypbind
dpkg -l | grep -i raid
dpkg -l | grep -i rpc

echo "Borrando la cuenta de Guest dado que es inseguro."

echo "[SeatDefaults]" >> /usr/share/lightdm/lightdm.conf.d/50-no-guest.conf
echo "allow-guest=false" >> /usr/share/lightdm/lightdm.conf.d/50-no-guest.conf

ls -1 /home > users

echo "Agregando variables de ambiente de usuarios."
cat users | while read LINE
do
  if [ -s /home/$LINE/.bashrc ]
  then
    echo "export JAVA_HOME=/usr/java/default" >> /home/$LINE/.bashrc
    echo "export JAVA_HOME=/usr/java/default" >> /root/.bashrc
    echo "export ANDROID=/home/$LINE/Development/adt-bundle-linux-x86_64-20140702" >> /home/$LINE/.bashrc
    echo "export ANDROID=/home/$LINE/Development/adt-bundle-linux-x86_64-20140702" >> /root/.bashrc
    echo "export PATH=/$JAVA_HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:\$ANDROID/eclipse:\$ANDROID/sdk/platform-tools" >> /home/$LINE/.bashrc
    echo "export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:/lib32:/usr/lib32" >> /home/$LINE/.bashrc
    echo "export CLASSPATH=/$JAVA_HOME/jre/lib/rt.jar:." >> /home/$LINE/.bashrc
  fi
done

echo "export PATH=\$JAVA_HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:\$ANDROID/eclipse:\$ANDROID/sdk/platform-tools" >> /root/.bashrc
echo "export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:/lib32:/usr/lib32" >> /root/.bashrc

echo "export CLASSPATH=\$JAVA_HOME/jre/lib/rt.jar:." >> /root/.bashrc
source /root/.bashrc

rm users


apt-get install -y nmap
echo "Generando un scaneo de los puertos abiertos."
nmap -sTU localhost

echo "Quitando servicios no requeridos."

service avahi-daemon stop
systemctl stop avahi-daemon.socket
systemctl stop avahi-daemon.service
systemctl disable avahi-daemon.service
systemctl disable avahi-daemon.socket
echo "manual" >> /etc/init/avahi-daemon.override

service cups-browsed stop
service cups stop
systemctl stop cups.path
systemctl stop cups-browsed.service
systemctl stop cups.service
systemctl stop cups.socket
systemctl disable cups.path
systemctl disable cups-browsed.service
systemctl disable cups.service
systemctl disable cups.socket
echo "manual" >> /etc/init/cups-browsed.override
echo "manual" >> /etc/init/cups.override

apt-get install -y libc6
apt-get install -y libstdc++6 libgcc1 zlib1g libncurses5 glibc-doc locales
wget http://dl.google.com/android/adt/adt-bundle-linux-x86_64-20140702.zip
unzip adt-bundle-linux-x86_64-20140702.zip

wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" http://download.oracle.com/otn-pub/java/jdk/8u111-b14/jdk-8u111-linux-x64.tar.gz
mkdir /usr/java
mv jdk-8u111-linux-x64.tar.gz /usr/java
cd /usr/java
tar zxvf jdk-8u111-linux-x64.tar.gz
ln -s jdk1.8.0_111 latest
ln -s latest defaultest
ln -s latest default
cd
source $HOME/.bashrc
java -version
javac -version

apt-get install -y vlc
apt-get install -y dia-libs

add-apt-repository ppa:kirillshkrogalev/ffmpeg-next
apt-get update
apt-get install -y ffmpeg
