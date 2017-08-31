#!bin/bash

rpm -qa | grep ftp
rpm -qa | grep telnet
rpm -qa | grep rdate
rpm -qa | grep rsh
rpm -qa | grep rlogin
rpm -qa | grep rtp
rpm -qa | grep rsync
rpm -qa | grep talk
rpm -qa | grep finger
rpm -qa | grep samba
rpm -qa | grep nfs
rpm -qa | grep isdn
rpm -qa | grep ypbind
rpm -qa | grep rpc
rpm -qa | grep vino
rpm -qa | grep vinagre
rpm -qa | grep openconnect
rpm -qa | grep vp
rpm -qa | grep ppp
rpm -qa | grep pptp
rpm -qa | grep raid
rpm -qa | grep torrent
rpm -qa | grep messenger
rpm -qa | grep xchat
rpm -qa | grep evolution

nmap -sTU localhost

google-chrome -version
firefox -version

ls /boot | grep -i vmlinuz

sudo nmap -sTU localhost

cat /etc/passwd
/usr/local/apache2/bin/apachectl start
ls -l /var/www
ls -l /usr/local
ls -l /usr/local/apache2

cat /etc/bashrc
service mariadb start


df -h
java -version
javac -version

g++ -o runcmasmas main.cpp -std=c++11
./runcmasmas

gcc -o runc main.c
./runc

javac Main.java
java Main

journalctl
tail -f /usr/local/apache2/log/access_log /usr/local/apache2/logs/error_log /var/log/apache2/access_log /var/log/apache2/error_log /var/log/mariadb/error.log
