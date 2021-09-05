current_dir="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"
. "$current_dir/../scripts/info.sh" && \
cd $current_dir && \
pdoc3 aqelib -f --html -o doc && \
pdoc3 aqelib --pdf > doc/aqelib-${version}.md && \
pandoc \
--metadata=title:"Aqemia molecular screening library documentation" \
--variable=documentclass:"extarticle" \
--variable=mainfont:"Roboto" \
--variable=mainfontoptions:"Extension=.ttf, UprightFont=*-Regular, BoldFont=*-Bold, ItalicFont=*-Italic, BoldItalicFont=*-BoldItalic" \
--variable=fontsize:"10pt" \
--variable=geometry:"margin=1.5cm,a4paper" \
--metadata=author:"BARRE kevin, DEBROISE Theau" \
--from=markdown+abbreviations+tex_math_single_backslash \
--pdf-engine=xelatex \
--toc --toc-depth=4 --output=doc/aqelib-${version}.pdf  doc/aqelib-${version}.md 
