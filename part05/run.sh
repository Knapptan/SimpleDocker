#!/bin/bash 

gcc server.c -lfcgi -o server
service nginx start
nginx -s reloud 
spawn-fcgi -p 8080 -n server