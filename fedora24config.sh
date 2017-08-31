#!bin/bash

whoami > quien
cat quien
a = "usuario"
echo $a
cat quien | while read LINE
do
	if [[ $quien != *"root"* ]]
		then
		echo "Deberias ser root para poder correr el script (no se puede con sudo)"
		exit 1
	fi
done
rm quien

echo "Listo para instalar"

dnf install libreoffice
dnf install cmake
dnf install cmake-curses-gui
dnf install k3b
dnf install xfce4-xkb-plugin
dnf install octave
dnf install scilab
dnf update firefox
firefox --version

echo "Instalando chrome"
dnf install libcurl
wget --no-check-certificate https://dl.google.com/linux/direct/google-chrome-stable_current_x86_64.rpm
dnf install google-chrome-stable_current_x86_64.rpm
rm google-chrome-stable_current_x86_64.rpm

echo "Removiendo programas inseguros"

rpm -e telnet-0.17-65.fc24.x86_64
rpm -e samba-common-4.4.3-1.fc24.noarch
rpm -e samba-client-4.4.3-1.fc24.x86_64
rpm -e --nodeps rpcbind-0.2.3-10.rc1.fc24.x86_64
rpm -e --nodeps nfs-utils-1.3.3-8.rc5.fc24.x86_64
rpm -e --nodeps xmlrpc-c-client-1.32.5-1909.svn2451.fc24.x86_64
rpm -e --nodeps xmlrpc-c-1.32.5-1909.svn2451.fc24.x86_64
rpm -e --nodeps vino-3.20.2-1.fc24.x86_64
rpm -e --nodeps vinagre-3.20.2-1.fc24.x86_64
rpm -e --nodeps openconnect-7.06-4.fc24.x86_64
rpm -e --nodeps NetworkManager-openconnect-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-openvpn-gnome-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-vpnc-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-openvpn-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-vpnc-gnome-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-vpnc-1.2.2-1.fc24.x86_64
rpm -e vpnc-0.5.3-27.svn550.fc24.x86_64
rpm -e openvpn-2.3.11-1.fc24.x86_64
rpm -e vpnc-script-20140805-4.gitdf5808b.fc24.noarch
rpm -e --nodeps ppp-2.4.7-9.fc24.x86_64
rpm -e NetworkManager-pptp-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-pptp-gnome-1.2.2-1.fc24.x86_64
rpm -e NetworkManager-pptp-1.2.2-1.fc24.x86_64
rpm -e rp-pppoe-3.12-5.fc24.x86_64
rpm -e --nodeps dmraid-1.0.0.rc16-30.fc24.x86_64
rpm -e dmraid-events-1.0.0.rc16-30.fc24.x86_64
rpm -e --nodeps evolution-3.20.2-1.fc24.x86_64
rpm -e --nodeps evolution-ews-3.20.2-1.fc24.x86_64
rpm -e --nodeps evolution-help-3.20.2-1.fc24.noarch
rpm -e gvfs-smb-1.28.2-1.fc24.x86_64

echo "Se verifica la existencia de algunos paquetes"

rpm -qa | grep -i mail
rpm -qa | grep -i evolution
rpm -qa | grep -i ftp
rpm -qa | grep -i talk
rpm -qa | grep -i finger
rpm -qa | grep -i telnet
rpm -qa | grep -i samba
rpm -qa | grep -i smb
rpm -qa | grep -i transmission
rpm -qa | grep -i torrent
rpm -qa | grep -i msn
rpm -qa | grep -i pidgin
rpm -qa | grep -i pptp
rpm -qa | grep -i ppp
rpm -qa | grep -i openconnect
rpm -qa | grep -i vpn
rpm -qa | grep -i rsh
rpm -qa | grep -i rlogin
rpm -qa | grep -i rtp
rpm -qa | grep -i rdate
rpm -qa | grep -i rsync
rpm -qa | grep -i vino
rpm -qa | grep -i vinagre
rpm -qa | grep -i nfs
rpm -qa | grep -i ypbind
rpm -qa | grep -i raid
rpm -qa | grep -i rpc

ls -1 /home > users

echo "Agregando variables de ambiente de usuarios."
cat users | while read LINE
do
  if [ -s /home/$LINE/.bashrc ]
  then
    echo "export JAVA_HOME=/usr/java/default" >> /home/$LINE/.bashrc
    echo "export CLASSPATH=\$JAVA_HOME/jre/lib/rt.jar:." >> /home/$LINE/.bashrc
  fi
done

echo "export JAVA_HOME=/usr/java/default" >> /root/.bashrc
echo "export PATH=\$JAVA_HOME/bin:/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin" >> /root/.bashrc
echo "export LD_LIBRARY_PATH=/lib:/usr/lib:/usr/local/lib:/lib32:/usr/lib32" >> /root/.bashrc
echo "export CLASSPATH=\$JAVA_HOME/jre/lib/rt.jar:." >> /root/.bashrc
source /root/.bashrc


source /etc/bashrc

rm users

dnf install nmap


echo "Quitando servicios no requeridos."

service avahi-daemon stop
systemctl stop avahi-daemon.socket
systemctl stop avahi-daemon.service
systemctl disable avahi-daemon.service
systemctl disable avahi-daemon.socket
echo "manual" >> /etc/init.d/avahi-daemon.override

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
echo "manual" >> /etc/init.d/cups.override

echo "Generando un scaneo de los puertos abiertos."
nmap -sTU localhost

dnf install libstdc++.x86_64 libgcc.x86_64 zlibrary.x86_64 glibc.x86_64 glibc-locale-source.x86_64
wget http://dl.google.com/android/adt/adt-bundle-linux-x86_64-20140702.zip
unzip adt-bundle-linux-x86_64-20140702.zip

dnf install gcc-c++
wget --no-check-certificate --no-cookies --header "Cookie: oraclelicense=accept-securebackup-cookie" http://download.oracle.com/otn-pub/java/jdk/8u111-b14/jdk-8u111-linux-x64.rpm
rpm -Uvh jdk-8u111-linux-x64.rpm
alternatives --install /usr/bin/java java /usr/java/jdk1.8.0_111/jre/bin/java 200000
alternatives --set java /usr/java/jdk1.8.0_111/jre/bin/java
alternatives --install /usr/bin/jar jar /usr/java/jdk1.8.0_111/bin/jar 200000
rm -f jdk*.rpm
source /etc/bashrc
java -version
javac -version