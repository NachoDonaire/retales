#!/bin/bash
sudo rm -f /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
sudo touch /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
sudo chmod +x  /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
sudo chmod  +w  /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
sudo chmod  +r /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
sudo echo "ctrl_interface=/run/wpa_supplicant" >> /etc/wpa_supplicant/wpa_supplicant-wlan0.conf
