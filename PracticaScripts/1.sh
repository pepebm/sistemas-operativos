#!/bin/bash
cat /var/log/auth.log | grep "session opened" | grep "systemd" | grep -v "lightdm" | cut -d ":" -f6 | cut -d " " -f6
