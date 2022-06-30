rm -r /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
touch /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
chmod g+w /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
chmod o+w /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
echo "ctrl_interface=/run/wpa_supplicant" >> /etc/wpa_supplicant/wpa_supplicant-wlan0.conf 
