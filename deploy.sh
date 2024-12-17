#!/bin/sh

SERVER=polaris
DIR=/var/www/html

hugo && rsync -avz --delete public/ --exclude=/.well-known $SERVER:${DIR}
