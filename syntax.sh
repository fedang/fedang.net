#!/bin/sh

# https://xyproto.github.io/splash/docs/all.html

LIGHT=xcode
DARK=modus-vivendi
CSS=assets/css/syntax.css

LIGHTHL="bg:#d0e0f0"
DARKHL="bg:#253040"

cat << EOF > $CSS
.cmd-user .cl::before {
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

.chroma code {
  padding: var(--pre-pad) 0;
}
.chroma .line {
  padding: 0 var(--pre-pad);
}
EOF

printf "\n/* Chroma style: %s */\n" $LIGHT >> $CSS
printf "@media (prefers-color-scheme: light) {\n" >> $CSS
hugo gen chromastyles --highlightStyle "$LIGHTHL" --style=$LIGHT >> $CSS
printf "}\n" >> $CSS
printf "\n\n/* Chroma style: %s */\n" $DARK >> $CSS
printf "@media (prefers-color-scheme: dark) {\n" >> $CSS
hugo gen chromastyles --highlightStyle "$DARKHL" --style=$DARK >> $CSS
printf "}\n" >> $CSS
