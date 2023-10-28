#!/bin/bash
xmake f -p linux -a x86_64 -m release
xmake -y
sleep 3