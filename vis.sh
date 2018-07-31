O="🔥"
o="⚡️"
X="🌳"
x="☘️"
point="💧"
star="⭐️"
nice="👍"

sed "s/O/$X/g" |
sed "s/X/$O/g" |
sed "s/x/$o/g" |
sed "s/o/$x/g" |
sed "s/\./$point/g" |
sed "s/*/$star/g" |
sed "s/<g☘️t/$nice/g" |
sed "s/Piece/Token/g" |
sed "s/(🌳)/$X/g" |
sed "s/(🔥)/$O/g" |
sed "s/Plateau/Map/g"
