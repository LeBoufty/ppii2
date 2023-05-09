#! /bin/bash
cd web
export FLASK_APP=potavisu.py
flask --debug run
read -s -n 1 -p