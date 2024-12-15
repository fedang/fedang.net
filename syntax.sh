#!/bin/sh

LIGHT=monokailight
DARK=onedark
CSS=assets/css/syntax.css

cat << EOF > $CSS
.cmd-user .line ::before {
  color: #669900;
  font-weight: bold;
  user-select: none;
  content: "user $"
  margin-right: 1em;
}
.cmd-root .line ::before {
  color: #ff3333;
  font-weight: bold;
  user-select: none;
  content: "root #"
  margin-right: 1em;
}
EOF

printf "\n/* Chroma style: %s */\n" $LIGHT >> $CSS
hugo gen chromastyles --style=$LIGHT >> $CSS
printf "\n\n/* Chroma style: %s */\n" $DARK >> $CSS
printf "@media (prefers-color-scheme: dark) {\n" >> $CSS
hugo gen chromastyles --style=$DARK >> $CSS
printf "}\n" >> $CSS
