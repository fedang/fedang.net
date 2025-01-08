#!/bin/sh

SERVER=polaris
DIR=/var/www/html

hugo --cleanDestinationDir && rsync -avz --delete public/ --exclude=/.well-known $SERVER:${DIR}
