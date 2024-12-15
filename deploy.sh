#!/bin/sh

USER=chad
HOST=fedang.net
DIR=/var/www/html

hugo && rsync -avz --delete public/ --exclude=/.well-known ${USER}@${HOST}:${DIR}
# this will delete everything on the server that's not in the local public folder

