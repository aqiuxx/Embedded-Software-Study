#!/bin/sh

# don't run if this package is removed but not purged
if [ ! -f /usr/sbin/popularity-contest ]; then
	exit 0
