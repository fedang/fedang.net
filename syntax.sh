#!/bin/sh

# https://xyproto.github.io/splash/docs/all.html

LIGHT=xcode
DARK=modus-vivendi
CSS=assets/css/syntax.css

cat << EOF > $CSS
.cmd-root .cl::before {
  color: #669900;
  font-weight: bold;
  user-select: none;
  content: "user $ ";
}
.cmd-root .cl::before {
  color: #ff3333;
  font-weight: bold;
  user-select: none;
  content: "root # ";
}
EOF

printf "\n/* Chroma style: %s */\n" $LIGHT >> $CSS
hugo gen chromastyles --style=$LIGHT >> $CSS
printf "\n\n/* Chroma style: %s */\n" $DARK >> $CSS
printf "@media (prefers-color-scheme: dark) {\n" >> $CSS
hugo gen chromastyles --style=$DARK >> $CSS
printf "}\n" >> $CSS
