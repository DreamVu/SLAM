printf 'set connection.id DirectConnect\nset ipv4.method manual\nset ipv4.addresses 192.168.0.175/24\nsave\nyes\nquit\n' | nmcli connection edit type ethernet
sudo su <<HERE
cat optimise_network_perf.txt >> /etc/sysctl.conf
HERE
