#!/bin/bash

git add .
git commit -am "Added new solutions"
git pull https://github.com/wechicken456/cses-solutions.git
git push -u origin master
